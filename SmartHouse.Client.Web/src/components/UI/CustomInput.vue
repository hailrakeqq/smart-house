<template>
  <div class="input-container">
    <label :for="id" class="input-label">{{ label }}</label>
    <input
      :type="type"
      :id="id"
      v-model="inputValue"
      @input="updateInput"
      class="input-field"
    />
    <div v-if="errorMessage" class="error-message">{{ errorMessage }}</div>
  </div>
</template>

<script lang="ts">
import { defineComponent, PropType } from "vue";

export default defineComponent({
  props: {
    id: {
      type: String,
      required: true,
    },
    label: {
      type: String,
      required: true,
    },
    type: {
      type: String,
      default: "text",
    },
    value: {
      type: [String, Number],
      default: "",
    },
    errorMessage: String,
  },
  data() {
    return {
      inputValue: this.value,
    };
  },
  methods: {
    updateInput(event: Event) {
      this.$emit("update:modelValue", (event.target as HTMLInputElement).value);
    },
  },
});
</script>

<style scoped>
.input-container {
  margin-bottom: 20px;
  width: 100%; /* Ensure the container takes full width */
}

.input-label {
  font-size: 16px;
  margin-bottom: 5px;
  display: block;
}

.input-field {
  width: 90%; /* Ensure the input takes full width */
  padding: 8px;
  font-size: 16px;
  border: 1px solid #ccc;
  border-radius: 5px;
}

.error-message {
  color: red;
  font-size: 14px;
  margin-top: 5px;
}
</style>
