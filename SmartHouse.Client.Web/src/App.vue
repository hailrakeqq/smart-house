<template>
  <nav>
    <div v-if="isUserExist">
      <router-link to="/">Home</router-link> |
      <router-link to="/account">Account</router-link> |
      <router-link to="/settings">Settings</router-link> |
      <router-link to="/about">About</router-link> |
      <a @click="logout">Logout</a>
    </div>
    <div v-else>
      <router-link to="/">Home </router-link> |
      <router-link to="/sign-in">Sign In </router-link> |
      <router-link to="/sign-up">Sign Up </router-link>
    </div>
  </nav>
  <router-view />
</template>

<script lang="ts">
import { defineComponent } from "vue";
export default defineComponent({
  name: "App",
  components: {},
  data() {
    return {
      isUserExist: false,
    };
  },

  mounted() {
    this.launchFunction();
  },
  methods: {
    logout() {
      localStorage.clear();
      this.$router.push("/");
      location.reload();
    },

    launchFunction() {
      const storedItem = localStorage.getItem("email");
      if (storedItem) {
        this.isUserExist = true;
      }
    },
  },
});
</script>

<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

nav {
  padding: 30px;

  a {
    cursor: pointer;
    font-weight: bold;
    color: #2c3e50;
    text-decoration: none;
    &.router-link-exact-active {
      color: #42b983;
    }
  }
}
</style>
