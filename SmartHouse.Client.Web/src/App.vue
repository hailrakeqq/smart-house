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
import axios from "axios";
export default defineComponent({
  name: "App",
  components: {},
  data(){
    return{
      intervalId: 0,
      request_frequency: 90,
      pingResult: null as number | null,
      uptime: ""
    }
  },
  created() {
    const frequencyString = localStorage.getItem("request_frequency");
    if (frequencyString !== null){ 
      this.request_frequency = parseInt(frequencyString as string, 10);
    } else {
      this.request_frequency = parseInt(prompt("Enter request frequency (90 seconds by default)", "90") || "90", 10);
      localStorage.setItem("request_frequency", this.request_frequency.toString());
    }
    this.getDeviceState();
    this.startInterval();
  },
  unmounted() {
    clearInterval(this.intervalId);
  },
  methods:{
    async getDeviceState() {   
      try {        
        await axios.get("/api/Main/getstate").then(response => {
          localStorage.setItem('monitoringData', JSON.stringify(response.data));
        })
      } catch (error) {
        console.error('Error pinging the server:', error);
      }
    },
    startInterval() {
      this.intervalId = setInterval(() => {
        this.getDeviceState();
      }, this.request_frequency * 1000);
    },
  }, 
});
</script>

<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #2c3e50;
  text-align:center;
  line-height: 2.0;
  word-spacing: 5px;
  letter-spacing:2.5px;
  font-size:18px;
}
.contect_block{
  text-align:left;
}
.label{
  font-weight:bold;

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
