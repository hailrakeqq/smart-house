<template>
  <div class="home">
    <h1>Logs</h1>
    <div class="sort-section">
      <input type="text" v-model="searchTerm" placeholder="Enter ID">
    </div>
    <div class="logs-container" v-if="searchTerm !== '' && searchTerm !== undefined">
      <div class="log-item" v-for="log in filteredLogs" :key="log.id">
        <p><strong>ID:</strong> {{ log.id }}</p>
        <p><strong>Log Level:</strong> {{ log.logLevel }}</p>
        <p><strong>Message:</strong> {{ log.message }}</p>
        <p><strong>Timestamp:</strong> {{ log.timestamp }}</p>
        <p><strong>Local IP:</strong> {{ log.localIP }}</p>
        <p><strong>External IP:</strong> {{ log.externalIP }}</p>
      </div>
    </div>
    <div class="logs-container" v-else>
      <div class="log-item" v-for="log in logs" :key="log.id">
        <p><strong>ID:</strong> {{ log.id }}</p>
        <p><strong>Log Level:</strong> {{ log.logLevel }}</p>
        <p><strong>Message:</strong> {{ log.message }}</p>
        <p><strong>Timestamp:</strong> {{ log.timestamp }}</p>
        <p><strong>Local IP:</strong> {{ log.localIP }}</p>
        <p><strong>External IP:</strong> {{ log.externalIP }}</p>
      </div>
    </div>
  </div>
</template>

<script>
import { defineComponent } from "vue";
import { Log } from "../Log";
import axios from "axios";

export default defineComponent({//TODO: fix log level
  name: "LogsView",
  components: {},
  data() {
    return {
      searchTerm: '',
      logs: []
    }
  },

  methods: {
    async getLogs() {
      try {
        const response = await axios.get("/api/Log/getlogs");
        return response.data;  
      } catch (error) {
        console.error('Error fetching data:', error);
        return []; 
      }
    },
  },

  async mounted() {
    this.logs = await this.getLogs();
  },
  computed: {
    filteredLogs: function() {
      return this.logs.filter(item => {
        return item.id.toString().includes(this.searchTerm)
      });
    }
  }
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

.sort-section {
  margin-bottom: 20px; 
  display: flex;
  align-items: center;
}

.sort-section p {
  margin-right: 10px; 
}


</style>