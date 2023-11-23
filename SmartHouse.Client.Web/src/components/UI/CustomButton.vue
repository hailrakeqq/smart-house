<template>
  <button
    :disabled="isButtonDisabled"
    class="custom-button"
    @click="handleClick"
  >
    <slot></slot>
  </button>
</template>

<script lang="ts">
import { defineComponent } from "vue";
export default defineComponent({
  props: {
    isButtonDisabled: {
      type: Boolean,
      required: false,
    },
  },
  methods: {
    handleClick() {
      this.$emit("click");
    },
  },
});
</script>

<style scoped>
.custom-button {
  background-color: #41b883;
  color: white;
  border: none;
  padding: 10px 20px;
  font-size: 16px;
  cursor: pointer;
  border-radius: 5px;
}

.custom-button:hover {
  background-color: #338a6e;
}
</style>
