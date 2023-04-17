import { Telegraf } from 'telegraf'
import express from 'express'
import fetch from 'node-fetch'
import dotenv from 'dotenv'
dotenv.config()

const app = express();
const bot = new Telegraf(process.env.TOKEN)
const chatId = process.env.CHAT_ID

// Устанавливаем обработчик для GET-запроса на сервере
app.get('/', (req, res) => {
  const message = req.query.message || 'Hello, client!';
  console.log(`Received a message from client: ${message}`);
  // Отправляем сообщение боту
  bot.telegram.sendMessage(chatId, message); //цифри == chat id
  res.send(`Message received: ${message}`);
});

// Запускаем сервер
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});

bot.on('message', (ctx) => {
  const message = ctx.message.text || 'Hello, server!';
  console.log(`Received a message from bot: ${message}`);
    if (message == "sendjson")
        ctx.telegram.sendMessage(chatId, JSON.stringify({ message: 'Hello, world!' }));
    try {
        // Отправляем сообщение клиенту
        fetch(`http://localhost:${PORT}/?message=${message}`)
          .then((res) => res.text())
          .then((text) => console.log(text))
          .catch((err) => console.error(err));
    } catch (error) {
        console.log(error.message)
    }
});



bot.launch()   
console.log("bot has been started");
// Enable graceful stop
process.once('SIGINT', () => bot.stop('SIGINT'))
process.once('SIGTERM', () => bot.stop('SIGTERM'))