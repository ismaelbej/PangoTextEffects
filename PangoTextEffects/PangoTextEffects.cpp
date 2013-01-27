#include <stdio.h>
#include <tchar.h>
#include <cairo/cairo.h>
#include <pango/pango.h>
#include <pango/pangocairo.h>

void pango_render_text_simple(cairo_t *context, PangoLayout *layout)
{
	cairo_new_path(context);
	cairo_move_to(context, 15.0, 10.0);

	pango_cairo_layout_path(context, layout);

	cairo_set_source_rgb(context, 0.9, 0.1, 0.8);
	cairo_fill(context);
}

void pango_render_text_border(cairo_t *context, PangoLayout *layout)
{
	cairo_new_path(context);
	cairo_move_to(context, 15.0, 10.0);

	pango_cairo_layout_path(context, layout);

	cairo_set_line_width(context, 6.0);
	cairo_set_miter_limit(context, 2.0);

	cairo_set_source_rgb(context, 0.0, 0.3, 0.9);
	cairo_stroke_preserve(context);

	cairo_set_source_rgb(context, 0.9, 0.1, 0.8);
	cairo_fill(context);
}

void pango_render_text_shadow(cairo_t *context, PangoLayout *layout)
{
	cairo_push_group(context);

	cairo_new_path(context);
	cairo_move_to(context, 15.0+8.0, 10.0+8.0);

	pango_cairo_layout_path(context, layout);

	cairo_set_line_width(context, 6.0);
	cairo_set_miter_limit(context, 2.0);

	cairo_set_source_rgb(context, 0.0, 0.0, 0.0);
	cairo_stroke_preserve(context);

	cairo_fill(context);

	cairo_pop_group_to_source(context);
	cairo_paint_with_alpha(context, 0.6);

	cairo_new_path(context);
	cairo_move_to(context, 15.0, 10.0);

	pango_cairo_layout_path(context, layout);

	cairo_set_line_width(context, 6.0);
	cairo_set_miter_limit(context, 2.0);

	cairo_set_source_rgb(context, 0.0, 0.3, 0.9);
	cairo_stroke_preserve(context);

	cairo_set_source_rgb(context, 0.9, 0.1, 0.8);
	cairo_fill(context);
}

void pango_render_text(char* message)
{
	cairo_surface_t *surface;
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 640, 480);

	cairo_t *context;
	context = cairo_create(surface);

	cairo_set_source_rgb(context, 1.0, 0.8, 0.4);
	cairo_paint(context);

	PangoLayout *layout;
	layout = pango_cairo_create_layout(context);

	pango_layout_set_text(layout, message, -1);

	PangoFontDescription *desc;
	desc = pango_font_description_from_string("Arial Bold 36");
	pango_layout_set_font_description(layout, desc);
	pango_font_description_free(desc);

	pango_layout_set_width(layout, 600 * PANGO_SCALE);
	pango_layout_set_height(layout, 400 * PANGO_SCALE);

	pango_cairo_update_layout(context, layout);

	//pango_render_text_simple(context, layout);
	//pango_render_text_border(context, layout);
	pango_render_text_shadow(context, layout);

	cairo_status_t status = cairo_surface_write_to_png(surface, "pango-text-effects.png");

	g_object_unref(layout);
	cairo_destroy(context);
	cairo_surface_destroy(surface);
}

char message[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
"Donec a diam lectus. Sed sit amet ipsum mauris. "
"Maecenas congue ligula ac quam viverra nec consectetur ante hendrerit. ";

int _tmain(int argc, _TCHAR* argv[])
{
	pango_render_text(message);

	return 0;
}
