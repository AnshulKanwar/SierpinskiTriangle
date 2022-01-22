#include <math.h>
#include <cairo/cairo.h>
#include <stdlib.h>
#include <stdio.h>

struct Point {
    float x;
    float y;
};

void draw_circle(cairo_t *cr, float x, float y, float radius) {
    cairo_move_to(cr, x, y);
    cairo_arc(cr, x, y, radius, 0., 2 * M_PI);
}

int SCR_WIDTH = 800;
int SCR_HEIGHT = 800;

int main() {
    int n;
    printf("Enter the number of points (enter a large number, for example 100000)\n");
    scanf("%d", &n);

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, SCR_WIDTH, SCR_HEIGHT);
    cairo_t *cr = cairo_create(surface);

    cairo_scale(cr, SCR_WIDTH, SCR_HEIGHT);

    struct Point p1, p2, p3;

    p1.x = (float)1/6;
    p1.y = (float)5/6;

    p2.x = (float)1/2;
    p2.y = (float)1/6;

    p3.x = (float)5/6;
    p3.y = (float)5/6;

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_paint(cr);

    cairo_set_source_rgb (cr, 0, 1, 0);

    float radius = 0.01;
    draw_circle(cr, p1.x, p1.y, radius);
    draw_circle(cr, p2.x, p2.y, radius);
    draw_circle(cr, p3.x, p3.y, radius);
    cairo_fill (cr);

    cairo_set_source_rgb(cr, 1, 0, 0);


    float x = 0.5;
    float y = 0.5;

    radius = 0.0005;
    draw_circle(cr, x, y, radius);

    for(int i=0; i<=n; i++) {
        int random = rand() % 3 + 1;
        if (random == 1)
        {
            x += (float)(p1.x - x) / 2;
            y += (float)(p1.y - y) / 2;
        }
        else if (random == 2)
        {
            x += (float)(p2.x - x) / 2;
            y += (float)(p2.y - y) / 2;
        }
        else if (random == 3)
        {
            x += (float)(p3.x - x) / 2;
            y += (float)(p3.y - y) / 2;
        }
        draw_circle(cr, x, y, radius);
    }

    cairo_fill (cr);
    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, "output.png");
    cairo_surface_destroy(surface);

    return 0;
}
