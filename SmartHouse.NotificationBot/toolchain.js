export class toolchain {
    static parseMessage(messageFromResponse) {
        if (!messageFromResponse.Message.includes('|'))
            return `Timestamp: ${messageFromResponse.Timestamp}\nMessage: ${messageFromResponse.Message}`;
        let resultMessage = messageFromResponse.message.replace('|', '\n')
        return `Timestamp: ${messageFromResponse.Timestamp}\nMessage: ${resultMessage}`
    }

    static water_keyboard = {
        inline_keyboard: [
            [{ text: "Close Servo", callback_data: "closeServo" }],
            [{ text: "Open Servo", callback_data: "openServo" }],
            [{ text: "Get Servo status", callback_data: "getServoStatus" }],  
        ] 
    }
}