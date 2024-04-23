<template>
  <div class="home">
    <h1>Hello world</h1>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
// import CustomInput from "../components/UI/CustomInput.vue";
import CustomButton from "../components/UI/CustomButton.vue";

export default defineComponent({
  name: "HomeView",
  components: {CustomButton},
  data(){
    return{
      intervalId: 0,
      request_frequency: 90,
      pingResult: null as number | null,
    }
  },
  created() {
    // Запускаем интервал при создании компонента
    this.startInterval();
    
    const frequencyString = localStorage.getItem("request_frequency");
    if (frequencyString !== null) this.request_frequency = parseInt(frequencyString as string, 10);
    else this.request_frequency = parseInt(prompt("Enter request frequency (90 seconds by default)", "90") || "90", 10);
  },
  unmounted() {
    clearInterval(this.intervalId);
  },
  methods:{
    async pingServer() {
      const startTime = performance.now(); // Get the current time before making the request
      
      try {
       
      } catch (error) {
        console.error('Error pinging the server:', error);
      }
    },
    startInterval() {
      this.intervalId = setInterval(() => {

      }, this.request_frequency * 1000);
    },
  }, 
  

});
</script>
