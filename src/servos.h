#ifndef SERVO_H
#define SERVO_H

class Servo
{

public:
    /**
     * @brief servo values representing different angles for the servo
     * 
     */
    unsigned short deg_0;
    unsigned short deg_180;
    unsigned short deg_90;
    /**
     * @brief the pin with which the servo is connected
     * 
     */
    unsigned char pin;
    /**
     * @brief initial servo value
     * 
     */
    unsigned short value = 3000;

    /**
     * @brief Construct a new Servo object
     * 
     * @param _deg_0 
     * @param _deg_90 
     * @param _deg_180 
     * @param _pin 
     */
    Servo(unsigned short _deg_0, unsigned short _deg_90, unsigned short _deg_180, unsigned char _pin) : deg_0(_deg_0), deg_180(_deg_180), deg_90(_deg_90), pin(_pin) {}
    
    /**
     * @brief Set the servo value corresponidg to the given angle
     * 
     * @param angle 
     */
    void setAngle(double angle);
    /**
     * @brief Set the servo value
     * 
     * @param _value 
     */
    void setValue(unsigned short _value);
    /**
     * @brief Get the servo value
     * 
     * @param angle 
     * @return unsigned short 
     */
    unsigned short getValue(double angle);
};

#endif
