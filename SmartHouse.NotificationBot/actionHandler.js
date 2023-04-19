import fetch from 'node-fetch'

export class ActionHandler{
    static closeServo(ctx) {
        fetch('http://192.168.15:5198/api/Home/CloseServo').then(res => res.status == 200 ?
            ctx.reply("servo was closed") : ctx.reply("error"))
    }

    static openServo(ctx) {
        fetch('http://192.168.15:5198/api/Home/OpenServo').then(res => res.status == 200 ?
            ctx.reply("servo was opened") : ctx.reply("error"))
    }

    static getServoStatus(ctx) {
        fetch('http://192.168.0.15:5198/api/Home/GetServoStatus')
    }
}
    