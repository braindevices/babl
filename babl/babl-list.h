/* babl - dynamically extendable universal pixel conversion library.
 * Copyright (C) 2005, Øyvind Kolås.
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

#ifndef _BABL_LIST_H
#define _BABL_LIST_H

#ifndef _BABL_CLASSES_H
#error  babl-list.h is only to be included after babl-classes.h
#endif


typedef struct _BablList BablList;

typedef struct _BablList
{
  int  count;
  int  size;
  Babl **items;
} _BablList;


BablList *
babl_list_init (void);

void
babl_list_destroy (BablList *list);

int
babl_list_size (BablList *list);

void
babl_list_insert (BablList *list,
                  Babl     *item);

void
babl_list_each_temp (BablList      *list,
                     BablEachFunction each_fun,
                     void             *user_data);


#endif
