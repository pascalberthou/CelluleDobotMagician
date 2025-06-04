#include <errno.h>
#include <modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const uint16_t UT_BITS_ADDRESS = 0x00; //0x130;
const uint16_t UT_BITS_NB = 0x01; //0x25;
const uint8_t UT_BITS_TAB[] = {0x00}; //{ 0xCD, 0x6B, 0xB2, 0x0E, 0x1B };
const uint16_t UT_BITS_ADDRESS_INVALID_REQUEST_LENGTH = UT_BITS_ADDRESS + 2;

const uint16_t UT_INPUT_BITS_ADDRESS = 0x01; //0x1C4;
const uint16_t UT_INPUT_BITS_NB = 0x01; //0x16;
const uint8_t UT_INPUT_BITS_TAB[] = {0x00}; //{ 0xAC, 0xDB, 0x35 };

const uint16_t UT_REGISTERS_ADDRESS = 0x160;
const uint16_t UT_REGISTERS_NB = 0x3;
const uint16_t UT_REGISTERS_NB_MAX = 0x20;
const uint16_t UT_REGISTERS_TAB[] = { 0x022B, 0x0001, 0x0064 };

const uint16_t UT_INPUT_REGISTERS_ADDRESS = 0x108;
const uint16_t UT_INPUT_REGISTERS_NB = 0x1;
const uint16_t UT_INPUT_REGISTERS_TAB[] = { 0x000A };


int main() {
    modbus_t *ctx;
    uint16_t tab_reg[32];
    int rc;

    // variables accessoires
    uint32_t new_response_to_sec;
    uint32_t new_response_to_usec;
    const int NB_REPORT_SLAVE_ID = 2 + 3 + strlen(LIBMODBUS_VERSION_STRING);
    uint8_t *tab_rp_bits = NULL;
    uint16_t *tab_rp_registers = NULL;
    uint16_t *tab_rp_registers_bad = NULL;
    int nb_points;

    // Créer un contexte Modbus
    ctx = modbus_new_tcp("169.254.250.222", 502);
   
    modbus_set_debug(ctx, TRUE);
    modbus_set_error_recovery(
        ctx, MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL);

    /* Allocate and initialize the memory to store the bits */
    nb_points = (UT_BITS_NB > UT_INPUT_BITS_NB) ? UT_BITS_NB : UT_INPUT_BITS_NB;
    tab_rp_bits = (uint8_t *) malloc(nb_points * sizeof(uint8_t));
    memset(tab_rp_bits, 0, nb_points * sizeof(uint8_t));

    printf("INPUT BITS=%d\n", nb_points);

    /* Allocate and initialize the memory to store the registers */
    nb_points = (UT_REGISTERS_NB > UT_INPUT_REGISTERS_NB) ? UT_REGISTERS_NB
                                                          : UT_INPUT_REGISTERS_NB;
    tab_rp_registers = (uint16_t *) malloc(nb_points * sizeof(uint16_t));
    memset(tab_rp_registers, 0, nb_points * sizeof(uint16_t));

    printf("1/1 No response timeout modification on connect: ");
    modbus_get_response_timeout(ctx, &new_response_to_sec, &new_response_to_usec);
  
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }
    else
        printf("Response time : %ds %dus\n", new_response_to_sec, new_response_to_usec);

    printf("\nTEST WRITE/READ:\n");

    /** COIL BITS **/

    /* Single */
    //rc = modbus_write_bit(ctx, UT_BITS_ADDRESS, ON);
    //printf("1/2 modbus_write_bit: ");

    rc = modbus_read_bits(ctx, UT_BITS_ADDRESS, 1, tab_rp_bits);
    printf("2/2 modbus_read_bits: %d\n",rc);

    modbus_close(ctx);
    modbus_free(ctx);
    printf("    modbus released\n");
    return 0;
}
