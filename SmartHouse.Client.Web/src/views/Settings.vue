<template>
  <dev class="settings_screen">
    <h1>Settings</h1>
    <div class="settings-item">
      <label for="request_frequency">Request Frequency:</label>
      <dev class="settings_inputs">
          <CustomInput id="request_frequency" class="input" type="number" v-model="request_frequency"/>
      </dev>
    </div>
    <CustomButton @click="saveSettings">Save</CustomButton>
  </dev>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import CustomInput from "../components/UI/CustomInput.vue";
import CustomButton from "../components/UI/CustomButton.vue";

export default defineComponent({
  components: {CustomInput, CustomButton},
  data(){
    return{
      request_frequency: '',
    }
  },

  methods:{
    updateRequestFrequency(value: string) {
      this.request_frequency = value;
    },
    saveSettings(){
      localStorage.setItem("request_frequency", this.request_frequency)
    }
  }
});
</script>

<style lang="css">

.settings_screen {
  margin-left: 100px;
  display: flex;
  flex-direction: column; 
  align-items: flex-start; 
}

.settings_inputs {
  display: flex;
  align-items: center;
  gap: 10px; 
}
.settings-item{
  display: flex;
  align-items: center; 
  gap: 10px;
}

label{
  margin-bottom: 5%;
}
</style>
