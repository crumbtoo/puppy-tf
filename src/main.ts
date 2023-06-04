const { Client, Events, GatewayIntentBits } = require('discord.js');

const client = new Client({ intents: [GatewayIntentBits.Guilds] });

client.once(Events.ClientReady, c => {
	console.log(`hi ${c.user.tag}`);
});

if(process.env["TOKEN"] === undefined)
	throw "set client token w/ $TOKEN (including the \"Bot \")"
else
	client.login(process.env["TOKEN"]);

