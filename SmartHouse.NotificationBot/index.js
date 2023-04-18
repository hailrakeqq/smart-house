import { Telegraf } from 'telegraf'
import express from 'express'
import fetch from 'node-fetch'
import dotenv from 'dotenv'
import {toolchain} from './toolchain.js'
dotenv.config()

const app = express();
const bot = new Telegraf(process.env.TOKEN)
const chatId = process.env.CHAT_ID

app.get('/', (req, res) => {
  const message = req.query.message || 'Hello, client!';
  console.log(`Received a message from client: ${message}`);
  bot.telegram.sendMessage(chatId, toolchain.parseMessage(message)); //цифри == chat id
  res.send(`Message received: ${message}`);
});


const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server listening on port ${PORT}`));

bot.on('message', (ctx) => {
  const message = ctx.message.text || 'Hello, server!';
  console.log(`Received a message from bot: ${message}`);
    try {
        fetch(`http://localhost:${PORT}/?message=${message}`)
          .then((res) => res.text())
          .then((text) => console.log(text))
          .catch((err) => console.error(err));
    } catch (error) { console.log(error.message) }
});

bot.launch()   
console.log("bot has been started");
// Enable graceful stop
process.once('SIGINT', () => bot.stop('SIGINT'))
process.once('SIGTERM', () => bot.stop('SIGTERM'))