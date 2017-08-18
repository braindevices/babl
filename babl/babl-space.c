/* babl - dynamically extendable universal pixel conversion library.
 * Copyright (C) 2017 Øyvind Kolås.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see
 * <http://www.gnu.org/licenses/>.
 */

#define MAX_SPACES   100

#include "config.h"
#include "babl-internal.h"
#include "base/util.h"

static BablSpace space_db[MAX_SPACES];

static void babl_chromatic_adaptation_matrix (const double *whitepoint,
                                              const double *target_whitepoint,
                                              double *chad_matrix)
{
  double bradford[9]={ 0.8951000, 0.2664000, -0.1614000,
                      -0.7502000, 1.7135000,  0.0367000,
                      0.0389000, -0.0685000, 1.0296000};
  double bradford_inv[9]={0.9869929,-0.1470543, 0.1599627,
                          0.4323053, 0.5183603, 0.0492912,
                          -0.0085287, 0.0400428, 0.9684867};

  double vec_a[3];
  double vec_b[3];

  babl_matrix_mul_vector (bradford, whitepoint, vec_a);
  babl_matrix_mul_vector (bradford, target_whitepoint, vec_b);

  memset (chad_matrix, 0, sizeof (double) * 9);

  chad_matrix[0] = vec_b[0] / vec_a[0];
  chad_matrix[4] = vec_b[1] / vec_a[1];
  chad_matrix[8] = vec_b[2] / vec_a[2];

  babl_matrix_mul_matrix (bradford_inv, chad_matrix, chad_matrix);
  babl_matrix_mul_matrix (chad_matrix, bradford, chad_matrix);
}

static void babl_space_compute_matrices (BablSpace *space)
{
#define _ space->
  /* transform spaces xy(Y) specified data to XYZ */
  double red_XYZ[3]        = { _ xr / _ yr, 1.0, ( 1.0 - _ xr - _ yr) / _ yr};
  double green_XYZ[3]      = { _ xg / _ yg, 1.0, ( 1.0 - _ xg - _ yg) / _ yg};
  double blue_XYZ[3]       = { _ xb / _ yb, 1.0, ( 1.0 - _ xb - _ yb) / _ yb};
  double whitepoint_XYZ[3] = { _ xw / _ yw, 1.0, ( 1.0 - _ xw - _ yw) / _ yw};
  double D50_XYZ[3]        = {0.9642,       1.0, 0.8249};
#undef _

  double mat[9] = {red_XYZ[0], green_XYZ[0], blue_XYZ[0],
                   red_XYZ[1], green_XYZ[1], blue_XYZ[1],
                   red_XYZ[2], green_XYZ[2], blue_XYZ[2]};
  double inv_mat[9];
  double S[3];
  double chad[9];

  babl_matrix_invert (mat, inv_mat);
  babl_matrix_mul_vector (inv_mat, whitepoint_XYZ, S);

  mat[0] *= S[0]; mat[1] *= S[1]; mat[2] *= S[2];
  mat[3] *= S[0]; mat[4] *= S[1]; mat[5] *= S[2];
  mat[6] *= S[0]; mat[7] *= S[1]; mat[8] *= S[2];

  babl_chromatic_adaptation_matrix (whitepoint_XYZ, D50_XYZ, chad);

  babl_matrix_mul_matrix (chad, mat, mat);

  memcpy (space->RGBtoXYZ, mat, sizeof (mat));
#if 0
  {
    int i;
    fprintf (stderr, "\n%s RGBtoXYZ:\n", space->name);
    for (i = 0; i < 9; i++)
    {
      fprintf (stderr, "%f ", mat[i]);
      if (i%3 == 2)
        fprintf (stderr, "\n");
    }
  }
#endif

  babl_matrix_invert (mat, mat);

#if 0
  {
    int i;
    fprintf (stderr, "\n%s XYZtoRGB:\n", space->name);
    for (i = 0; i < 9; i++)
    {
      fprintf (stderr, "%f ", mat[i]);
      if (i%3 == 2)
        fprintf (stderr, "\n");
    }
  }
#endif

  memcpy (space->XYZtoRGB, mat, sizeof (mat));
}

void
babl_space_get_chromaticities (const Babl *space,
                               double *xw, double *yw,
                               double *xr, double *yr,
                               double *xg, double *yg,
                               double *xb, double *yb)
{
  if (!space)
    return;

  if (xw) *xw = space->space.xw;
  if (yw) *yw = space->space.yw;

  if (xr) *xr = space->space.xr;
  if (yr) *yr = space->space.yr;
  if (xg) *xg = space->space.xg;
  if (yg) *yg = space->space.yg;
  if (xb) *xb = space->space.xb;
  if (yb) *yb = space->space.yb;
}

BablTRC babl_space_get_trc (const Babl *space, double *gamma)
{
  if (!space)
    return 0;
  if (gamma) *gamma = space->space.gamma;
  return space->space.trc;
}

const Babl *
babl_space (const char *name)
{
  int i;
  for (i = 0; space_db[i].instance.class_type; i++)
    if (!strcmp (space_db[i].instance.name, name))
      return (Babl*)&space_db[i];
  return NULL;
}

const Babl *
babl_space_new (const char *name,
                double wx, double wy,
                double rx, double ry,
                double gx, double gy,
                double bx, double by,
                double gamma, BablTRC trc)
{
  int i=0;
  static BablSpace space;
  space.instance.class_type = BABL_SPACE;
  space.instance.id         = 0;

  space.xr = rx;
  space.yr = ry;
  space.xg = gx;
  space.yg = gy;
  space.xb = bx;
  space.yb = by;
  space.xw = wx;
  space.yw = wy;
  space.gamma = gamma;
  space.trc = trc;

  for (i = 0; space_db[i].instance.class_type; i++)
  {
    int offset = ((char*)&space_db[i].xr) - (char*)(&space_db[i]);
    int size   = ((char*)&space_db[i].trc) - ((char*)&space_db[i].xr);

    if (memcmp ((char*)(&space_db[i]) + offset, ((char*)&space) + offset, size)==0)
      {
        return (void*)&space_db[i];
      }
  }
  if (i >= MAX_SPACES-1)
  {
    babl_log ("too many BablSpaces");
    return NULL;
  }
  space_db[i]=space;
  space_db[i].instance.name = space_db[i].name;
  if (name)
    sprintf (space_db[i].name, "%s", name);
  else
    sprintf (space_db[i].name, "space-%.4f,%.4f_%.4f,%.4f_%.4f,%.4f_%.4f,%.4f_%.4f,%i",
             wx,wy,rx,ry,bx,by,gx,gy,gamma,trc);

  /* compute matrixes */
  babl_space_compute_matrices (&space_db[i]);

  return (Babl*)&space_db[i];
}

void
babl_space_class_for_each (BablEachFunction each_fun,
                           void            *user_data)
{
  int i=0;
  for (i = 0; space_db[i].instance.class_type; i++)
    if (each_fun (BABL (&space_db[i]), user_data))
      return;
}

void
babl_space_class_init (void)
{
  /* we register sRGB first so that lookups for it is fastest */
#ifdef CCE
  babl_space_new ("sRGB",
                  0.3127, 0.3290, /* D65 */
                  0.6400,  0.3300,
                  0.3000,  0.6000,
                  0.1500,  0.0600,
                  1.0, BABL_TRC_LINEAR);
#else
  babl_space_new ("sRGB",
                  0.3127,  0.3290, /* D65 */
                  //0.3127, 0.3290, /* D65 */
                  0.6400,  0.3300,
                  0.3000,  0.6000,
                  0.1500,  0.0600,
                  2.2, BABL_TRC_SRGB);
#endif

  babl_space_new ("Adobe",
                  0.3127,  0.3290, /* D65 */
                  0.6400,  0.3300,
                  0.2100,  0.7100,
                  0.1500,  0.0600,
                  2.2, BABL_TRC_GAMMA);

  babl_space_new ("Apple",
                  0.3127,  0.3290, /* D65 */
                  0.6250,  0.3400,
                  0.2800,  0.5950,
                  0.1550,  0.0700,
                  1.8, BABL_TRC_GAMMA);

  babl_space_new ("Best",
                  0.34567, 0.3585,  /* D50 */
                  0.7347,  0.2653,
                  0.2150,  0.7750,
                  0.1300,  0.0350,
                  2.2, BABL_TRC_GAMMA);

  babl_space_new ("Beta",
                  0.34567, 0.3585,  /* D50 */
                  0.6888,  0.3112,
                  0.1986,  0.7551,
                  0.1265,  0.0352,
                  2.2, BABL_TRC_GAMMA);

  babl_space_new ("ProPhoto",
                  0.34567, 0.3585,  /* D50 */
                  0.7347,  0.2653,
                  0.1596,  0.8404,
                  0.0366,  0.0001,
                  1.8, BABL_TRC_GAMMA);

  babl_space_new ("Bruce",
                  0.3127,  0.3290, /* D65 */
                  0.6400,  0.3300,
                  0.2800,  0.6500,
                  0.1500,  0.0600,
                  1.8, BABL_TRC_GAMMA);

  babl_space_new ("PAL",
                  0.3127,  0.3290, /* D65 */
                  0.6400,  0.3300,
                  0.2900,  0.6000,
                  0.1500,  0.0600,
                  2.2, BABL_TRC_GAMMA);

  babl_space_new ("SMPTE-C",
                  0.3127,  0.3290, /* D65 */
                  0.6300,  0.3300,
                  0.3100,  0.5950,
                  0.1550,  0.0700,
                  2.2, BABL_TRC_GAMMA);

  babl_space_new ("ColorMatch",
                  0.34567, 0.3585,  /* D50 */
                  0.6300,  0.3400,
                  0.2950,  0.6050,
                  0.1500,  0.0750,
                  1.8, BABL_TRC_GAMMA);

  babl_space_new ("Don RGB 4",
                  0.34567, 0.3585,  /* D50 */
                  0.6960,  0.3000,
                  0.2150,  0.7650,
                  0.1300,  0.0350,
                  1.8, BABL_TRC_GAMMA);

  babl_space_new ("WideGamutRGB",
                  0.34567, 0.3585,  /* D50 */
                  0.7350,  0.2650,
                  0.1150,  0.8260,
                  0.1570,  0.0180,
                  2.2, BABL_TRC_GAMMA);
}

void babl_space_to_xyz (const Babl *space, const double *rgb, double *xyz)
{
  _babl_space_to_xyz (space, rgb, xyz);
}

void babl_space_from_xyz (const Babl *space, const double *xyz, double *rgb)
{
  _babl_space_from_xyz (space, xyz, rgb);
}
