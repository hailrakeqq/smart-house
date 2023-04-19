export class toolchain {
    static parseMessage(message) {
        if (!message.includes('|'))
            return message;
        let resultMessage = message.replace('|', '\n')
        return resultMessage
    }

    static water_keyboard = {
        inline_keyboard: [
            [{ text: "Close Servo", callback_data: "closeServo" }],
            [{ text: "Open Servo", callback_data: "openServo" }],
            [{ text: "Get Servo status", callback_data: "getServoStatus" }],  
        ] 
    }
}