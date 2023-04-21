import { Telegraf, Markup } from 'telegraf'
import express from 'express'
import fetch from 'node-fetch'
import dotenv from 'dotenv'
import { toolchain } from './toolchain.js'
import {ActionHandler} from './actionHandler.js'
dotenv.config()

const app = express();
global.bot = new Telegraf(process.env.TOKEN)
const chatId = process.env.CHAT_ID

app.get('/', (req, res) => {
  const response = req.query.message || 'Hello, client!';
  console.log(`\n\nReceived a message from client: ${response}`);
  
  const parsedMessage = JSON.parse(response)
  const messageFromResponse = toolchain.parseMessage(parsedMessage)

  if (parsedMessage.Type === "warning water message") {   
    bot.telegram.sendMessage(
      chatId,
      messageFromResponse,
      { reply_markup: toolchain.water_keyboard });
  } else {
    bot.telegram.sendMessage(
      chatId,
      messageFromResponse)
  }
  res.send(`Message received: ${response}`);
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server listening on port ${PORT}`));

bot.command("menu", async ctx => {
	    return await ctx.reply(
		    "Here our menu",
		    Markup.keyboard([
			    ["☸ Setting"],
			    ["⭐️ Links"], 
		      ]).oneTime().resize(),
	    );
    });

bot.hears("☸ Setting", ctx => ctx.reply('here be settings!'))

bot.hears("⭐️ Links", async ctx => {
	    return await ctx.reply(
        "Links: ",
        Markup.inlineKeyboard([
          [Markup.button.url("Site", "https://github.com/hailrakeqq/smart-house")],
          [Markup.button.url("⭐️ Github", "https://github.com/hailrakeqq/smart-house")]
        ])
  )
})

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

//bot action section:
bot.action('closeServo', ActionHandler.closeServo);
bot.action('openServo', ActionHandler.openServo);
bot.action('getServoStatus', ActionHandler.getServoStatus);


bot.launch()   

// Enable graceful stop
process.once('SIGINT', () => bot.stop('SIGINT'))
process.once('SIGTERM', () => bot.stop('SIGTERM'))