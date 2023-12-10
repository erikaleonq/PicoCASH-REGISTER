#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>
#include <hardware/gpio.h>
#include <string.h>

// Define GPIO pins for RC522 module
#define RC522_RST_PIN 0
#define RC522_SDA_PIN 1
#define RC522_SCK_PIN 2
#define RC522_MOSI_PIN 3
#define RC522_MISO_PIN 4
// SPI configuration
typedef struct spi_inst spi_inst_t;
#define spi0 ((spi_inst_t *)spi0_hw)

// RC522 commands
const uint8_t PICC_REQUEST = 0x26;
const uint8_t PICC_ANTENNA_ON = 0x01;
const uint8_t MIFARE_READ = 0x30;
const uint8_t MIFARE_WRITE = 0xA2;

// Function to initialize the RC522 module
void rc522_init() {
    // Initialize the RST pin as GPIO output
    gpio_init(RC522_RST_PIN);
    gpio_set_dir(RC522_RST_PIN, GPIO_OUT);
    gpio_put(RC522_RST_PIN, 0); // Set RST pin to low for reset
    // Initialize the SPI interface
    spi_init(spi0,48000);
    sleep_ms(2);
    gpio_put(RC522_RST_PIN, 1); // Set RST pin to low for reset

}

// Function to read a block from the RFID card
uint8_t *rc522_read_block(uint8_t block_number) {
    // Allocate memory for the block data
    uint8_t *block_data = malloc(16);

    // Create a buffer to hold the command and response
    uint8_t tx_buffer[16] = {MIFARE_READ, block_number};
    uint8_t rx_buffer[16];

    // Send the READ command and receive the response
    spi_write_read_blocking(spi0, tx_buffer, rx_buffer, 16);

    printf("Resultado PICC_REQUEST: %02X\n", rx_buffer[0]);

    // Check the error code in the response
    if (rx_buffer[0] != 0x00) {
        free(block_data);
        return NULL;
    }

    // Copy 15 bytes of block data from the response
    memcpy(block_data, &rx_buffer[1], 15);

    return block_data;
}


// Function to write a block to the RFID card
void rc522_write_block(uint8_t block_number, uint8_t *block_data) {
    // Create a buffer to hold the command and block data
    uint8_t tx_buffer[18];

    // Construct the WRITE command
    tx_buffer[0] = MIFARE_WRITE;
    tx_buffer[1] = block_number;

    // Copy the block data to the buffer
    memcpy(&tx_buffer[2], block_data, 16);

    // Send the WRITE command and receive the response
    spi_write_blocking(spi0, tx_buffer, 18);
}

// Function to check the presence of an RFID tag
int rc522_check_tag() {

  uint8_t tx_buffer[2] = {PICC_REQUEST, 0x26}; 
  uint8_t rx_buffer[2];
  
  spi_write_read_blocking(spi0, tx_buffer, rx_buffer, 2);

  if ((rx_buffer[0] & 0xF0) != 0x10) {
    return 0; 
  }
  
  tx_buffer[0] = PICC_ANTENNA_ON;
  spi_write_read_blocking(spi0, tx_buffer, rx_buffer, 2); 

  return (rx_buffer[0] == 0x10) && (rx_buffer[1] == 0x00);  
}


void rc522_get_uid(uint8_t* uid) {

  uint8_t tx_buffer[2] = {PICC_REQUEST, 0x26};
  uint8_t rx_buffer[18];

  // Request UID
  spi_write_read_blocking(spi0, tx_buffer, rx_buffer, 2); 

  printf("Resultado PICC_REQUEST: %02X\n", rx_buffer[0]);
  
  if ((rx_buffer[0] & 0xF0) != 0x10) {
    // No card present
    return; 
  }

  // Anti-collision, get serial number
  tx_buffer[0] = 0x93;
  tx_buffer[1] = 0x20;


  spi_write_read_blocking(spi0, tx_buffer, rx_buffer, 18);

  // Copy UID to output buffer  
  memcpy(uid, &rx_buffer[1], 5); 
}

// Function to test the RC522 module
int main() {
  // Initialize the RC522 module
  stdio_init_all();
  rc522_init();

  while (1) {
  
      uint8_t *block_data = rc522_read_block(40);
      printf("Resultado block data: %02X\n", block_data);

      
    sleep_ms(1000);  // Wait for 1 second
  }

  return 0;
}
