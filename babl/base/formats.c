/* babl - dynamically extendable universal pixel conversion library.
 * Copyright (C) 2006, Øyvind Kolås.
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
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "babl.h"
#include "babl-ids.h"
#include "babl-base.h"

void
babl_formats_init (void)
{
  babl_format_new (
    babl_model_id (BABL_RGBA_GAMMA_2_2),
    babl_type_id (BABL_DOUBLE),
    babl_component_id (BABL_RED_GAMMA_2_2),
    babl_component_id (BABL_GREEN_GAMMA_2_2),
    babl_component_id (BABL_BLUE_GAMMA_2_2),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_GAMMA_2_2),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_RED_GAMMA_2_2),
    babl_component_id (BABL_GREEN_GAMMA_2_2),
    babl_component_id (BABL_BLUE_GAMMA_2_2),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_GAMMA_2_2),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_RED_GAMMA_2_2),
    babl_component_id (BABL_GREEN_GAMMA_2_2),
    babl_component_id (BABL_BLUE_GAMMA_2_2),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_GAMMA_2_2),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_RED_GAMMA_2_2),
    babl_component_id (BABL_GREEN_GAMMA_2_2),
    babl_component_id (BABL_BLUE_GAMMA_2_2),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_GAMMA_2_2_PREMULTIPLIED),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_RED_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_GREEN_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_BLUE_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_GAMMA_2_2_PREMULTIPLIED),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_RED_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_GREEN_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_BLUE_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_GAMMA_2_2_PREMULTIPLIED),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_RED_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_GREEN_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_BLUE_GAMMA_2_2_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGB_GAMMA_2_2),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_RED_GAMMA_2_2),
    babl_component_id (BABL_GREEN_GAMMA_2_2),
    babl_component_id (BABL_BLUE_GAMMA_2_2),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGB_GAMMA_2_2),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_RED_GAMMA_2_2),
    babl_component_id (BABL_GREEN_GAMMA_2_2),
    babl_component_id (BABL_BLUE_GAMMA_2_2),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGB_GAMMA_2_2),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_RED_GAMMA_2_2),
    babl_component_id (BABL_GREEN_GAMMA_2_2),
    babl_component_id (BABL_BLUE_GAMMA_2_2),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2_ALPHA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2_ALPHA_PREMULTIPLIED),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMA_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2_ALPHA),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_LUMA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2_ALPHA_PREMULTIPLIED),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_LUMA_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_LUMA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2_ALPHA),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_LUMA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2_ALPHA_PREMULTIPLIED),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_LUMA_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_GAMMA_2_2),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_LUMA),
    NULL);
  babl_format_new (
    "name", "Y'CbCr u8",
    babl_model_id (BABL_YCBCR),
    babl_type_id (BABL_U8_LUMA),
    babl_component_id (BABL_LUMA),
    babl_type_id (BABL_U8_CHROMA),
    babl_component_id (BABL_CB),
    babl_component_id (BABL_CR),
    NULL);
  babl_format_new (
    babl_model_id (BABL_YCBCR),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_CB),
    babl_component_id (BABL_CR),
    NULL);
  babl_format_new (
    babl_model_id (BABL_YCBCR_ALPHA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_CB),
    babl_component_id (BABL_CR),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_RED),
    babl_component_id (BABL_GREEN),
    babl_component_id (BABL_BLUE),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_RED),
    babl_component_id (BABL_GREEN),
    babl_component_id (BABL_BLUE),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA),
    babl_type_id (BABL_DOUBLE),
    babl_component_id (BABL_RED),
    babl_component_id (BABL_GREEN),
    babl_component_id (BABL_BLUE),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_RED),
    babl_component_id (BABL_GREEN),
    babl_component_id (BABL_BLUE),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_PREMULTIPLIED),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_RED_MUL_ALPHA),
    babl_component_id (BABL_GREEN_MUL_ALPHA),
    babl_component_id (BABL_BLUE_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_PREMULTIPLIED),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_RED_MUL_ALPHA),
    babl_component_id (BABL_GREEN_MUL_ALPHA),
    babl_component_id (BABL_BLUE_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGBA_PREMULTIPLIED),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_RED_MUL_ALPHA),
    babl_component_id (BABL_GREEN_MUL_ALPHA),
    babl_component_id (BABL_BLUE_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGB),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_RED),
    babl_component_id (BABL_GREEN),
    babl_component_id (BABL_BLUE),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGB),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_RED),
    babl_component_id (BABL_GREEN),
    babl_component_id (BABL_BLUE),
    NULL);
  babl_format_new (
    babl_model_id (BABL_RGB),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_RED),
    babl_component_id (BABL_GREEN),
    babl_component_id (BABL_BLUE),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_ALPHA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMINANCE),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_ALPHA_PREMULTIPLIED),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMINANCE_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMINANCE),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_ALPHA),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_LUMINANCE),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_ALPHA_PREMULTIPLIED),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_LUMINANCE_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY),
    babl_type_id (BABL_U16),
    babl_component_id (BABL_LUMINANCE),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_ALPHA),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_LUMINANCE),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY_ALPHA_PREMULTIPLIED),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_LUMINANCE_MUL_ALPHA),
    babl_component_id (BABL_ALPHA),
    NULL);
  babl_format_new (
    babl_model_id (BABL_GRAY),
    babl_type_id (BABL_U8),
    babl_component_id (BABL_LUMINANCE),
    NULL);

  /* overriding name, since the generated name would be wrong due
   * to differing types
   */
  babl_format_new (
    "name", "Y'CbCr u8",
    babl_model_id (BABL_YCBCR),
    babl_type_id (BABL_U8_LUMA),
    babl_component_id (BABL_LUMA),
    babl_type_id (BABL_U8_CHROMA),
    babl_component_id (BABL_CB),
    babl_component_id (BABL_CR),
    NULL);
  babl_format_new (
    babl_model_id (BABL_YCBCR),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_CB),
    babl_component_id (BABL_CR),
    NULL);
  babl_format_new (
    babl_model_id (BABL_YCBCR_ALPHA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_LUMA),
    babl_type_id (BABL_FLOAT),
    babl_component_id (BABL_CB),
    babl_component_id (BABL_CR),
    babl_component_id (BABL_ALPHA),
    NULL);
}
