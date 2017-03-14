/* GStreamer
 * Copyright (C) 2010 Sebastian Dröge <sebastian.droege@collabora.co.uk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __GST_CLIMAGE_FREEZE_H__
#define __GST_CLIMAGE_FREEZE_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_CLIMAGE_FREEZE \
  (gst_climage_freeze_get_type())
#define GST_CLIMAGE_FREEZE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_CLIMAGE_FREEZE,GstCLImageFreeze))
#define GST_CLIMAGE_FREEZE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_CLIMAGE_FREEZE,GstCLImageFreezeClass))
#define GST_CLIMAGE_FREEZE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj),GST_TYPE_CLIMAGE_FREEZE,GstCLImageFreezeClass))
#define GST_IS_CLIMAGE_FREEZE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_CLIMAGE_FREEZE))
#define GST_IS_CLIMAGE_FREEZE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_CLIMAGE_FREEZE))

typedef struct _GstCLImageFreeze GstCLImageFreeze;
typedef struct _GstCLImageFreezeClass GstCLImageFreezeClass;

struct _GstCLImageFreeze
{
  GstElement parent;

  /* < private > */
  GstPad *sinkpad;
  GstPad *srcpad;

  GMutex lock;
  GstBuffer *buffer;
  gint fps_n, fps_d;

  GstSegment segment;
  gboolean need_segment;
  guint seqnum;

  guint64 offset;

  /* TRUE if currently doing a flushing seek, protected
   * by srcpad's stream lock */
  gint seeking;
    
    /* Duration got from client */
    guint64 m_duration;
    
    /* velocity matrix for duration calculation */
    float m_velocity[3];
};

struct _GstCLImageFreezeClass
{
  GstElementClass parent_class;
};

GST_EXPORT
GType gst_climage_freeze_get_type (void);

G_END_DECLS

#endif /* __GST_CLIMAGE_FREEZE_H__ */
