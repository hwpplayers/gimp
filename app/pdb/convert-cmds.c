/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl. */

#include "config.h"

#include <gegl.h>

#include "pdb-types.h"

#include "core/gimpimage-convert.h"
#include "core/gimpimage.h"
#include "core/gimpitemstack.h"
#include "core/gimppalette.h"
#include "core/gimpparamspecs.h"

#include "gimppdb.h"
#include "gimppdberror.h"
#include "gimppdb-utils.h"
#include "gimpprocedure.h"
#include "internal-procs.h"

#include "gimp-intl.h"


static GValueArray *
image_convert_rgb_invoker (GimpProcedure      *procedure,
                           Gimp               *gimp,
                           GimpContext        *context,
                           GimpProgress       *progress,
                           const GValueArray  *args,
                           GError            **error)
{
  gboolean success = TRUE;
  GimpImage *image;

  image = gimp_value_get_image (&args->values[0], gimp);

  if (success)
    {
      if (gimp_pdb_image_is_not_base_type (image, GIMP_RGB, error))
        {
          success = gimp_image_convert (image, GIMP_RGB,
                                        0, 0, FALSE, FALSE, 0, NULL,
                                        NULL, error);
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GValueArray *
image_convert_grayscale_invoker (GimpProcedure      *procedure,
                                 Gimp               *gimp,
                                 GimpContext        *context,
                                 GimpProgress       *progress,
                                 const GValueArray  *args,
                                 GError            **error)
{
  gboolean success = TRUE;
  GimpImage *image;

  image = gimp_value_get_image (&args->values[0], gimp);

  if (success)
    {
      if (gimp_pdb_image_is_not_base_type (image, GIMP_GRAY, error))
        {
          success = gimp_image_convert (image, GIMP_GRAY,
                                        0, 0, FALSE, FALSE, 0, NULL,
                                        NULL, error);
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GValueArray *
image_convert_indexed_invoker (GimpProcedure      *procedure,
                               Gimp               *gimp,
                               GimpContext        *context,
                               GimpProgress       *progress,
                               const GValueArray  *args,
                               GError            **error)
{
  gboolean success = TRUE;
  GimpImage *image;
  gint32 dither_type;
  gint32 palette_type;
  gint32 num_cols;
  gboolean alpha_dither;
  gboolean remove_unused;
  const gchar *palette;

  image = gimp_value_get_image (&args->values[0], gimp);
  dither_type = g_value_get_enum (&args->values[1]);
  palette_type = g_value_get_enum (&args->values[2]);
  num_cols = g_value_get_int (&args->values[3]);
  alpha_dither = g_value_get_boolean (&args->values[4]);
  remove_unused = g_value_get_boolean (&args->values[5]);
  palette = g_value_get_string (&args->values[6]);

  if (success)
    {
      GimpPalette *pal = NULL;

      if (gimp_pdb_image_is_not_base_type (image, GIMP_INDEXED, error) &&
          gimp_item_stack_is_flat (GIMP_ITEM_STACK (gimp_image_get_layers (image))))
        {
          switch (palette_type)
            {
            case GIMP_MAKE_PALETTE:
              if (num_cols < 1 || num_cols > MAXNUMCOLORS)
                success = FALSE;
              break;

            case GIMP_CUSTOM_PALETTE:
              pal = gimp_pdb_get_palette (gimp, palette, FALSE, error);
              if (! pal)
                {
                  success = FALSE;
                }
              else if (pal->n_colors > MAXNUMCOLORS)
                {
                  g_set_error_literal (error,
                                       GIMP_PDB_ERROR,
                                       GIMP_PDB_ERROR_INVALID_ARGUMENT,
                                       _("Cannot convert to a palette "
                                         "with more than 256 colors."));
                  success = FALSE;
                }
              break;

            default:
              break;
            }
        }
      else
        {
          success = FALSE;
        }

      if (success)
        success = gimp_image_convert (image, GIMP_INDEXED,
                                      num_cols, dither_type,
                                      alpha_dither, remove_unused,
                                      palette_type, pal,
                                      NULL, error);
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GValueArray *
image_convert_set_dither_matrix_invoker (GimpProcedure      *procedure,
                                         Gimp               *gimp,
                                         GimpContext        *context,
                                         GimpProgress       *progress,
                                         const GValueArray  *args,
                                         GError            **error)
{
  gboolean success = TRUE;
  gint32 width;
  gint32 height;
  gint32 matrix_length;
  const guint8 *matrix;

  width = g_value_get_int (&args->values[0]);
  height = g_value_get_int (&args->values[1]);
  matrix_length = g_value_get_int (&args->values[2]);
  matrix = gimp_value_get_int8array (&args->values[3]);

  if (success)
    {
      if (width == 0 || height == 0 || matrix_length == width * height)
        {
          gimp_image_convert_set_dither_matrix (matrix, width, height);
        }
      else
        {
          g_set_error_literal (error, GIMP_PDB_ERROR,
                               GIMP_PDB_ERROR_INVALID_ARGUMENT,
                               "Dither matrix length must be width * height");
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

void
register_convert_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-image-convert-rgb
   */
  procedure = gimp_procedure_new (image_convert_rgb_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-image-convert-rgb");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-image-convert-rgb",
                                     "Convert specified image to RGB color",
                                     "This procedure converts the specified image to RGB color. This process requires an image in Grayscale or Indexed color mode. No image content is lost in this process aside from the colormap for an indexed image.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_image_id ("image",
                                                         "image",
                                                         "The image",
                                                         pdb->gimp, FALSE,
                                                         GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-image-convert-grayscale
   */
  procedure = gimp_procedure_new (image_convert_grayscale_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-image-convert-grayscale");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-image-convert-grayscale",
                                     "Convert specified image to grayscale (256 intensity levels)",
                                     "This procedure converts the specified image to grayscale with 8 bits per pixel (256 intensity levels). This process requires an image in RGB or Indexed color mode.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_image_id ("image",
                                                         "image",
                                                         "The image",
                                                         pdb->gimp, FALSE,
                                                         GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-image-convert-indexed
   */
  procedure = gimp_procedure_new (image_convert_indexed_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-image-convert-indexed");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-image-convert-indexed",
                                     "Convert specified image to and Indexed image",
                                     "This procedure converts the specified image to 'indexed' color. This process requires an image in RGB or Grayscale mode. The 'palette_type' specifies what kind of palette to use, A type of '0' means to use an optimal palette of 'num_cols' generated from the colors in the image. A type of '1' means to re-use the previous palette (not currently implemented). A type of '2' means to use the so-called WWW-optimized palette. Type '3' means to use only black and white colors. A type of '4' means to use a palette from the gimp palettes directories. The 'dither type' specifies what kind of dithering to use. '0' means no dithering, '1' means standard Floyd-Steinberg error diffusion, '2' means Floyd-Steinberg error diffusion with reduced bleeding, '3' means dithering based on pixel location ('Fixed' dithering).",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_image_id ("image",
                                                         "image",
                                                         "The image",
                                                         pdb->gimp, FALSE,
                                                         GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_enum ("dither-type",
                                                  "dither type",
                                                  "The dither type to use",
                                                  GIMP_TYPE_CONVERT_DITHER_TYPE,
                                                  GIMP_NO_DITHER,
                                                  GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_enum ("palette-type",
                                                  "palette type",
                                                  "The type of palette to use",
                                                  GIMP_TYPE_CONVERT_PALETTE_TYPE,
                                                  GIMP_MAKE_PALETTE,
                                                  GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("num-cols",
                                                      "num cols",
                                                      "The number of colors to quantize to, ignored unless (palette_type == GIMP_MAKE_PALETTE)",
                                                      G_MININT32, G_MAXINT32, 0,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_boolean ("alpha-dither",
                                                     "alpha dither",
                                                     "Dither transparency to fake partial opacity",
                                                     FALSE,
                                                     GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_boolean ("remove-unused",
                                                     "remove unused",
                                                     "Remove unused or duplicate color entries from final palette, ignored if (palette_type == GIMP_MAKE_PALETTE)",
                                                     FALSE,
                                                     GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("palette",
                                                       "palette",
                                                       "The name of the custom palette to use, ignored unless (palette_type == GIMP_CUSTOM_PALETTE)",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-image-convert-set-dither-matrix
   */
  procedure = gimp_procedure_new (image_convert_set_dither_matrix_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-image-convert-set-dither-matrix");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-image-convert-set-dither-matrix",
                                     "Set dither matrix for conversion to indexed",
                                     "This procedure sets the dither matrix used when converting images to INDEXED mode with positional dithering.",
                                     "David Gowers",
                                     "David Gowers",
                                     "2006",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("width",
                                                      "width",
                                                      "Width of the matrix (0 to reset to default matrix)",
                                                      G_MININT32, G_MAXINT32, 0,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("height",
                                                      "height",
                                                      "Height of the matrix (0 to reset to default matrix)",
                                                      G_MININT32, G_MAXINT32, 0,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("matrix-length",
                                                      "matrix length",
                                                      "The length of 'matrix'",
                                                      1, 1024, 1,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int8_array ("matrix",
                                                           "matrix",
                                                           "The matrix -- all values must be >= 1",
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}
