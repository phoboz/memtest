#include <jagdefs.h>
#include <jagtypes.h>

#include <stdlib.h>

#include <interrupt.h>
#include <display.h>
#include <sprite.h>
#include <screen.h>
#include <joypad.h>
#include <sound.h>

#ifdef DEBUG
#include <console.h>
FILE *fp;
#endif

#include "config.h"
#define VBL_PERIOD     60
#define ALLOC_MODULO   3
#define ALLOC_ADD_SIZE (100*1024)

display *game_display;
joypad_state *js;
unsigned int vbl_count;
unsigned long vbl_periods;
volatile unsigned int new_alloc;
size_t alloc_size;

void *gpu_addr;

static void vbl_handler(void);

int main(int argc, char *argv[]) {
  TOMREGS->vmode = CRY16|CSYNC|BGEN|PWIDTH4|VIDEN;
  init_interrupts();
  init_display_driver();

  gpu_addr = &_GPU_FREE_RAM;
  
  game_display = new_display(0);

  memset((void *) TOMREGS->clut1, 0, 256 * sizeof(uint16_t));
  vbl_count = 0;
  vbl_periods = 0;
  new_alloc = 0;
  alloc_size = ALLOC_ADD_SIZE;

  show_display(game_display);

#ifdef DEBUG
  fp = open_custom_console(
    game_display,
    0,
    0,
    CONSOLE_COLOR_INDEX,
    40,
    24,
    15
    );
#endif

  js = malloc(sizeof(joypad_state));

  vblQueue[0] = vbl_handler;

  while (1) {
    vsync();

    // move
    read_joypad_state(js);

    if (new_alloc)
    {
      char *buf = (char *) malloc(alloc_size);
      if (buf != NULL)
      {
        memset(buf, rand()%0xff, alloc_size);
        fprintf(fp, "Allocated %ld kB at :%lx\n", alloc_size / 1024, (unsigned long) buf);
        alloc_size += ALLOC_ADD_SIZE;
      }
      else
      {
        fprintf(fp, "Alloc failed at %ld bytes\n", alloc_size);
      }

      new_alloc = 0;
    }
    wait_display_refresh();

    // update
  }
}

static void vbl_handler(void)
{
  if (++vbl_count >= VBL_PERIOD)
  {
#ifdef DEBUG
    fprintf(fp, "Vertical blank period(s): %ld\n", vbl_periods);
#endif

    vbl_count = 0;
    if ((++vbl_periods) % ALLOC_MODULO == 0)
    {
      new_alloc = 1;
    }
  }
}

