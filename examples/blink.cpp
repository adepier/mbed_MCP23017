/**
 * On every loop, the state of the port B is copied to port A.
 *
 * Use active low inputs on port B. Internal pullups are enabled by default by the library so there is no need for external resistors.
 * Place LEDS on port A for instance.
 * When pressing a button, the corresponding led is shut down.
 *
 * You can also uncomment one line to invert the input (when pressing a button the corresponding led is lit)
 */
#include <mbed.h>
#include <MCP23017.h>

// Nucleo L432KC
#define I2C_SDA PA_10
#define I2C_SCL PA_9
I2C i2c(I2C_SDA, I2C_SCL);

#define MCP23017_ADDR 0x20
MCP23017 mcp = MCP23017(MCP23017_ADDR, i2c);

 

int main()
{
     printf("start i2c\r\n");
    i2c.start();
    // check i2c
    printf("check i2c\n");
    char outByte = 0x00;

    int returnCode = -1;
    while (returnCode != 0)
    {
        returnCode = i2c.write((MCP23017_ADDR << 1), &outByte, 1, 0);
        if (returnCode == 0)
        {
            printf("I2C device found at address 0x%X\r\n", MCP23017_ADDR);
        }
    }
    printf("init MCP23017\n");
     /** Reset MCP23017 device to its power-on state
     */    
     mcp.reset();
     
     /** Configure an MCP23017 device
     *
     * @param   dir_config         data direction value (1 = input, 0 = output)
     * @param   pullup_config      100k pullup value (1 = enabled, 0 = disabled)
     * @param   polarity_config    polarity value (1 = flip, 0 = normal)
     */ 
    mcp.config(DIR_OUTPUT,0,0);

    printf("end setup\n");
     
    while (true)
    {
        printf("forward\n");
        mcp.write_bit(0,0);
        mcp.write_bit(1,1);
        ThisThread::sleep_for(chrono::milliseconds(2000)); 
        printf("backward\n");   
        mcp.write_bit(1,0);
        mcp.write_bit(0,1);
         ThisThread::sleep_for(chrono::milliseconds(2000)); 
    }
}