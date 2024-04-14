<template>
  <header>
    <div class="wrapper">
      <nav>
        <RouterLink class="item" to="/">Home</RouterLink>
        <RouterLink class="item" to="/logs">Logs</RouterLink>
        <RouterLink class="item" to="/settings">Settings</RouterLink>
      </nav>
    </div>
  </header>
  <RouterView />
</template>
<script lang="ts">
import { defineComponent } from "vue";
import { RouterLink, RouterView } from 'vue-router'
export default defineComponent({
  name: "App",
  components: {},
  data() {
    return {};
  },

  methods: {},
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
  .wrapper{
  background-color: #f7f7f7;
  border: 1px solid #ddd;
  border-radius: 5px;
  box-shadow: 0 2px 2px rgba(0, 0, 0, 0.3);
  padding: 20px;
  margin: 20px 0;
  display: flex;
  flex-direction: column;
}
  .item{
    padding-left: 30px;
  }
  .selectedList{
    margin-right: 25px;
    display: inline-block;
    float: right;
  }
}
</style>
