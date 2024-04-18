<template>
  <div class="input-container">  
    <input :value="modelValue" @input="updateInput" class="input-field" type="text">
  </div>
</template>
  
  <script>
  export default {
  name: "CustomInput",
    props:{
      modelValue: [String, Number]
    },
    methods:{
      updateInput(event){
        this.$emit('update:modelValue', event.target.value)
      }
    }
  }
  </script>
  
<style scoped>
 
.input-container {
  margin-bottom: 20px;
  width: 100%; /* Ensure the container takes full width */
}

.input-field {
  width: 90%; /* Ensure the input takes full width */
  padding: 8px;
  font-size: 16px;
  border: 1px solid #ccc;
  border-radius: 5px;
}
  
</style>
