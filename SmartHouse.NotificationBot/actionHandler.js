import fetch from 'node-fetch'

export class ActionHandler{
    static closeServo(ctx) {
        fetch('http://192.168.15:5198/api/Home/CloseServo')
    }

    static openServo(ctx) {
        fetch('http://192.168.15:5198/api/Home/OpenServo')
    }

    static getServoStatus(ctx) {
        fetch('http://192.168.0.15:5198/api/Home/GetServoStatus')
    }
}
    