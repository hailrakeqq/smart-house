import { createRouter, createWebHistory, RouteRecordRaw } from "vue-router";
import HomeView from "../views/HomeView.vue";
import SignIn from "../components/SignIn.vue";
import SignUp from "../components/SignUp.vue";
import Account from "../components/Account.vue";
import Settings from "../components/Settings.vue";

const routes: Array<RouteRecordRaw> = [
  {
    path: "/",
    name: "home",
    component: HomeView,
  },
  {
    path: "/sign-in",
    name: "sign in",
    component: SignIn,
  },
  {
    path: "/sign-up",
    name: "sign up",
    component: SignUp,
  },
  {
    path: "/account",
    name: "account",
    component: Account,
  },
  {
    path: "/settings",
    name: "settings",
    component: Settings,
  },
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
});

export default router;
