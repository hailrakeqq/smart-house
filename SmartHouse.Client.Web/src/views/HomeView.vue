<template>
  <div class="home">
    <h1>Main page</h1>
    <div id="monitoringWindow">
      <div class="monitoring-item">
        <span class="label">Log Level:</span>
        <span class="value">{{ deviceState.logLevel }}</span>
      </div>
      <div class="monitoring-item">
        <span class="label">User Email:</span>
        <span class="value">{{ deviceState.userEmail }}</span>
      </div>
      <div class="monitoring-item">
        <span class="label">Valve State:</span>
        <span class="value">{{ deviceState.valveState }}</span>
      </div>
      <div class="monitoring-item">
        <span class="label">Water Level:</span>
        <span class="value">{{ deviceState.waterLevel }}</span>
      </div>
      <div class="monitoring-item">
        <span class="label">Uptime:</span>
        <span class="value">{{ deviceState.uptime }}</span>
      </div>
      <div class="monitoring-item">
        <span class="label">Ping Result:</span>
        <span class="value">{{ deviceState.pingResult }}</span>
      </div>
      <div class="monitoring-item">
        <span class="label">Local IP:</span>
        <span class="value">{{ deviceState.localIP }}</span>
      </div>
      <div class="monitoring-item">
        <span class="label">External IP:</span>
        <span class="value">{{ deviceState.externalIP }}</span>
      </div>
    </div>

    <CustomButton>Close Valve</CustomButton>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import CustomButton from "../components/UI/CustomButton.vue";
import axios from "axios";

interface DeviceState {
  logLevel: string;
  userEmail: string;
  valveState: string;
  waterLevel: number;
  uptime: number;
  pingResult: string;
  localIP: string;
  externalIP: string;
}

export default defineComponent({
  name: "HomeView",
  components: { CustomButton },
  data() {
    return {
      deviceState: {} as DeviceState 
    };
  },
  mounted() {
    Object.assign(this.deviceState, JSON.parse(localStorage.getItem("monitoringData") || "{}"));
  },
  methods: {
    
  }, 
});
</script>
