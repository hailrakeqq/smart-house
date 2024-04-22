<template>
    <div class="home">
      <h1>Logs</h1>
      <div class="logs-container">
      <div
        class="log-item"
        v-for="log in logs"
        v-bind:key="log.id">
        <p><strong>ID:</strong> {{log.id}}</p>
        <p><strong>Log Level:</strong> {{log.logLevel}}</p>
        <p><strong>Message:</strong> {{log.message}}</p>
        <p><strong>Timestamp:</strong> {{log.timestamp}}</p>
        <p><strong>Local IP:</strong> {{log.localIP}}</p>
        <p><strong>External IP:</strong> {{log.externalIP}}</p>
      </div>
    </div>
   
    </div>
  </template>
  
  <script lang="ts">
  import { defineComponent } from "vue";
  import {Log} from "../Log"
  import axios from "axios";
  export default defineComponent({
    name: "LogsView",
    components: {},
    data(){
      return{
        logs: [] as Log[],
      }
    },

    methods:{
      async getLogs() {
        try {
          const response = await axios.get("/api/Log/getlogs");
          console.log("Response data:", response.data);
          return response.data;  
        } catch (error) {
          console.error('Error fetching data:', error);
          return []; 
        }
      }
    },

    async mounted() {
      this.logs = await this.getLogs()
    },

  });
  </script>

<style>
.home {
  font-family: Arial, sans-serif;
  padding: 20px;
}

h1 {
  color: #333;
  text-align: center;
}

.logs-container {
  display: flex;
  flex-direction: column; 
  gap: 20px; 
}

.log-item {
  border: 1px solid #ccc;
  border-radius: 5px;
  padding: 20px;
  padding-bottom: 0px;
  width: 100%;
  box-sizing: border-box;
  display: flex;
  flex-direction: column; 
  align-items: flex-start; 
}

.log-detail {
  margin: 3px 0;
  text-align: left;

}

p {
  margin: 5px;
}

.log-detail strong {
  font-weight: bold;
  margin-right: 5px;
}
</style>