/* babl - dynamically extendable universal pixel conversion library.
 * Copyright (C) 2005, Øyvind Kolås.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
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

#include <string.h>
#include <stdarg.h>

#include "babl-internal.h"
#include "babl-db.h"


static int 
each_babl_type_destroy (Babl *babl,
                        void *data)
{
  babl_free (babl->type.from);
  babl_free (babl);
  return 0;  /* continue iterating */
}


static Babl *
type_new (const char  *name,
          int          id,
          int          bits)
{
  Babl *babl;

  babl_assert (bits != 0);
  babl_assert (bits % 8 == 0);
  
  babl                = babl_malloc (sizeof (BablType) + strlen (name) + 1);
  babl->instance.name = (void*) babl + sizeof (BablType);
  babl->class_type    = BABL_TYPE;
  babl->instance.id   = id;
  strcpy (babl->instance.name, name);
  babl->type.bits     = bits;
  babl->type.from     = NULL;

  return babl;
}

Babl *
babl_type_new (void *first_arg,
               ...)
{
  va_list  varg;
  Babl    *babl;
  int      id         = 0;
  int      is_integer = 0;
  int      bits       = 0;
  long     min        = 0;
  long     max        = 255;
  double   min_val    = 0.0;
  double   max_val    = 0.0;

  const char *arg=first_arg;

  va_start (varg, first_arg);
  
  while (1)
    {
      arg = va_arg (varg, char *);
      if (!arg)
        break;
     
      if (BABL_IS_BABL (arg))
        {
#ifdef BABL_LOG
          Babl *babl = (Babl*)arg;

          babl_log ("%s unexpected", babl_class_name (babl->class_type));
#endif
        }
      /* if we didn't point to a babl, we assume arguments to be strings */
      else if (!strcmp (arg, "id"))
        {
          id = va_arg (varg, int);
        }
      
      else if (!strcmp (arg, "bits"))
        {
          bits = va_arg (varg, int);
          min = 0;
          max = 1<<bits;
        }
      else if (!strcmp (arg, "integer"))
        {
          is_integer = va_arg (varg, int);
        }
      else if (!strcmp (arg, "min"))
        {
          min = va_arg (varg, long);
        }
      else if (!strcmp (arg, "max"))
        {
          max = va_arg (varg, long);
        }
      else if (!strcmp (arg, "min_val"))
        {
          min_val = va_arg (varg, double);
        }
      else if (!strcmp (arg, "max_val"))
        {
          max_val = va_arg (varg, double);
        }
      
      else
        {
          babl_fatal ("unhandled argument '%s' for format '%s'", arg, first_arg);
        }
    }
    
  va_end   (varg);

  babl = type_new (first_arg, id, bits);

  { 
    Babl *ret = babl_db_insert (db, babl);
    if (ret!=babl)
        babl_free (babl);
    return ret;
  }
}

BABL_CLASS_TEMPLATE (type)
