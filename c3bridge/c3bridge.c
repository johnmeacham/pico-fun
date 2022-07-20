#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>
#include "editline.h"
#include "hardware/uart.h"

struct editline elstate = EDITLINE_INIT;


void user_putchar(char ch)
{
        putchar((unsigned char)ch);
}

const char editline_help_string[] = "\
Editing commands:\n\
  ^P (Up arrow)    - previous from history\n\
  ^N (Down arrow)  - next from history\n\
  ^F (Right arrow) - move cursor one character forward\n\
  ^B (Left arrow)  - move cursor one character backwards\n\
  ^A (Home)        - move cursor to begining of line\n\
  ^E (End)         - move cursor to end of line\n\
  ^D (Delete)      - delete character under cursor\n\
  ^H (Backspace)   - delete character before cursor\n\
  ^Q               - erase whole line\n\
  ^K               - delete from cursor until end of line\n\
  ^U               - delete from cursor until beginning of line\n\
  ^L               - clear and redraw screen\n\
  ^M (Enter)       - enter command\n\
  ^T               - transpose characters, dragging character forward.\n\
  ^W               - delete to beginning of current word\n\
  ALT-Backspace    - delete to beginning of current word\n\
  ALT-d            - delete to end of current word\n\
  ALT-u            - uppercase word\n\
  ALT-l            - lowercase word\n\
  ALT-c            - capitalize word\n\
  ALT-f            - move to next end of word\n\
  ALT-b            - move to previous beginning of word\n\
  ALT-a            - move to beginning of current word\n\
  ALT-e            - move to end of current word\n\
  ALT-t            - exchange previous with current word\n\
";

int main(int argc, char *argv[])
{
				stdio_init_all();
				uart_init(uart1, 115200);
				gpio_set_function(8, GPIO_FUNC_UART);
				gpio_set_function(9, GPIO_FUNC_UART);
				gpio_set_function(10, GPIO_FUNC_UART);
				gpio_set_function(11, GPIO_FUNC_UART);
				uart_set_hw_flow(uart1,true,true);
				uart_set_format(uart1,8,1,UART_PARITY_NONE);
				uart_set_translate_crlf(uart1,false);

				while(!stdio_usb_connected())
								tight_loop_contents();
				puts(editline_help_string);
				editline_command_complete(&elstate, false);
				while(1) {
								if(uart_is_readable_within_us(uart1,0)) {
												editline_hide_command(&elstate);
												while(uart_is_readable_within_us(uart1,100))
																putchar(uart_getc(uart1));
												editline_restore_command(&elstate);
												fflush(stdout);
								}

								int ch = getchar_timeout_us(0);
								if (ch != PICO_ERROR_TIMEOUT) {

												switch (editline_process_char(&elstate, ch)) {
												case EL_REDRAW:
																puts(editline_help_string);
																break;
												case EL_COMMAND:
																uart_puts(uart1, elstate.buf);
																uart_puts(uart1, "\r\n");
																editline_command_complete(&elstate, true);
																break;
												default:
																break;
												}
								}
				}
}


