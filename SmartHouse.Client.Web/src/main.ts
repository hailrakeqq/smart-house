import { createApp } from "vue";
import App from "./App.vue";
import router from "./router";
import axios from "axios";

axios.defaults.baseURL = "http://localhost:5198";
const app = createApp(App).use(router);

app.config.globalProperties.$axios = axios;
app.mount("#app");
