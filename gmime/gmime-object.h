/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  Authors: Jeffrey Stedfast <fejj@ximian.com>
 *
 *  Copyright 2001-2004 Ximian, Inc. (www.ximian.com)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Street #330, Boston, MA 02111-1307, USA.
 *
 */


#ifndef __GMIME_OBJECT_H__
#define __GMIME_OBJECT_H__

#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus */

#include <glib.h>
#include <glib-object.h>

#include <gmime/gmime-type-utils.h>
#include <gmime/gmime-content-type.h>
#include <gmime/gmime-stream.h>
#include <gmime/gmime-header.h>

#define GMIME_TYPE_OBJECT            (g_mime_object_get_type ())
#define GMIME_OBJECT(obj)            (GMIME_CHECK_CAST ((obj), GMIME_TYPE_OBJECT, GMimeObject))
#define GMIME_OBJECT_CLASS(klass)    (GMIME_CHECK_CLASS_CAST ((klass), GMIME_TYPE_OBJECT, GMimeObjectClass))
#define GMIME_IS_OBJECT(obj)         (GMIME_CHECK_TYPE ((obj), GMIME_TYPE_OBJECT))
#define GMIME_IS_OBJECT_CLASS(klass) (GMIME_CHECK_CLASS_TYPE ((klass), GMIME_TYPE_OBJECT))
#define GMIME_OBJECT_GET_CLASS(obj)  (GMIME_CHECK_GET_CLASS ((obj), GMIME_TYPE_OBJECT, GMimeObjectClass))

typedef struct _GMimeObject GMimeObject;
typedef struct _GMimeObjectClass GMimeObjectClass;

struct _GMimeObject {
	GObject parent_object;
	
	GMimeContentType *content_type;
	GMimeHeader *headers;
	
	char *content_id;
};

struct _GMimeObjectClass {
	GObjectClass parent_class;
	
	void         (*init)          (GMimeObject *object);
	
	void         (*add_header)    (GMimeObject *object, const char *header, const char *value);
	void         (*set_header)    (GMimeObject *object, const char *header, const char *value);
	const char * (*get_header)    (GMimeObject *object, const char *header);
	void         (*remove_header) (GMimeObject *object, const char *header);
	
	void         (*set_content_type) (GMimeObject *object, GMimeContentType *content_type);
	
	char *       (*get_headers)   (GMimeObject *object);
	
	ssize_t      (*write_to_stream) (GMimeObject *object, GMimeStream *stream);
};


typedef void (*GMimePartFunc) (GMimeObject *part, gpointer data);


GType g_mime_object_get_type (void);

void g_mime_object_register_type (const char *type, const char *subtype, GType object_type);
GMimeObject *g_mime_object_new_type (const char *type, const char *subtype);

#ifndef GMIME_DISABLE_DEPRECATED
void g_mime_object_ref (GMimeObject *object);
void g_mime_object_unref (GMimeObject *object);
#endif

void g_mime_object_set_content_type (GMimeObject *object, GMimeContentType *mime_type);
const GMimeContentType *g_mime_object_get_content_type (GMimeObject *object);

void g_mime_object_set_content_type_parameter (GMimeObject *object, const char *name, const char *value);
const char *g_mime_object_get_content_type_parameter (GMimeObject *object, const char *name);

void g_mime_object_set_content_id (GMimeObject *object, const char *content_id);
const char *g_mime_object_get_content_id (GMimeObject *object);

void g_mime_object_add_header (GMimeObject *object, const char *header, const char *value);
void g_mime_object_set_header (GMimeObject *object, const char *header, const char *value);
const char *g_mime_object_get_header (GMimeObject *object, const char *header);
void g_mime_object_remove_header (GMimeObject *object, const char *header);

char *g_mime_object_get_headers (GMimeObject *object);

ssize_t g_mime_object_write_to_stream (GMimeObject *object, GMimeStream *stream);
char *g_mime_object_to_string (GMimeObject *object);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GMIME_OBJECT_H__ */
