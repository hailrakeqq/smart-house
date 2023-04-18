export class toolchain {
    static parseMessage(message) {
        if (!message.includes('|'))
            return message;
        let resultMessage = message.replace('|', '\n')
        return resultMessage
    }
}