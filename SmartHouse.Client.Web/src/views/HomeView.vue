<template>
  <div class="home">
    <div class="contect_block">
      <div class="monitoring-window-container">
        <div id="monitoringWindow" class="monitoring-window">

        <div class="monitoring-item">
          <span class="label">User Email: </span>
          <span class="value">{{ deviceState.userEmail }}</span>
        </div>
        <div class="monitoring-item">
          <span class="label">Water Level: </span>
          <span class="value">{{ deviceState.waterLevel }} cm</span>
        </div>
        <div class="monitoring-item">
          <span class="label">Uptime: </span>
          <span class="value">{{ deviceState.uptime }}</span>
        </div>
        <div class="monitoring-item">
          <span class="label">Ping Result: </span>
          <span class="value">{{ deviceState.pingResult }}</span>
        </div>
        <div class="monitoring-item">
          <span class="label">Local IP: </span>
          <span class="value">{{ deviceState.localIP }}</span>
        </div>
        <div class="monitoring-item">
          <span class="label">External IP: </span>
          <span class="value">{{ deviceState.externalIP }}</span>

        </div>
        <div id="valve-state" class="valve-state">
          <div class="image" v-if="deviceState.valveState == 'True'">
            <img src="../../public/open.png" alt="Пример изображения">
          </div>
          <div class="image" v-if="deviceState.valveState == 'False'">
            <img src="../../public/close.png" alt="Пример изображения">
          </div>
          <span class="label">Valve State: </span>
          <span class="value" v-if="deviceState.valveState == 'True'">Open</span>
          <span class="value" v-if="deviceState.valveState == 'False'">Close</span>
          <div class="btn">
            <CustomButton @click="closeRequest" v-if="deviceState.valveState == 'True'">Close Valve</CustomButton>
            <CustomButton @click="openRequest" v-if="deviceState.valveState == 'False'">Open Valve</CustomButton>
          </div>
        </div>
      </div>
      </div>
    </div>
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
    this.updateData();
  },
  methods: {
    async openRequest() {
      await axios.post(`http://${this.deviceState.localIP}:80/open`).then(result => {
        alert(result.data)
        setInterval(()=>location.reload(), 50)
      });
    },
    async closeRequest() {
      await axios.post(`http://${this.deviceState.localIP}:80/close`).then(result => {
        alert(result.data)
        setInterval(()=>location.reload(), 50)
      });
    },

    updateData() {
      setInterval(() => {
        Object.assign(this.deviceState, JSON.parse(localStorage.getItem("monitoringData") || "{}"));
      }, parseInt(localStorage.getItem("request_frequency") || "60") * 1000);
    }
  },
});
</script>

<style>
img {
  width: 20%;
  height: 20%;
}

.btn {
  top: 430px;
  left: 150px;
  margin-left: 6%;
}

.monitoring-window-container {
  display: flex;
  flex-direction: row;
  margin-left: 10%;
}

.monitoring-window {
  flex: 1;
}

.valve-state {
  margin-left: 20px;
  margin-top: 3%;
}
</style>
