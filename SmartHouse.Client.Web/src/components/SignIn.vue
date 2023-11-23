<template>
  <div>
    <h2>Sign In</h2>
    <form @submit.prevent="signIn" class="form-container">
      <CustomInput
        id="Email"
        name="email"
        label="Email:"
        type="email"
        v-model="email"
        placeholder="Enter your Email"
      />
      <span v-if="!isEmailValid">Please enter email.</span>

      <CustomInput
        id="password"
        label="Password:"
        type="password"
        v-model="password"
        placeholder="Enter your password"
      />
      <span v-if="!isPasswordValid">Please enter valid password.</span>

      <CustomButton
        :is-button-disabled="isButtonDisabled"
        class="btn"
        @click="signIn"
        >Sign In</CustomButton
      >
    </form>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import CustomButton from "./UI/CustomButton.vue";
import CustomInput from "./UI/CustomInput.vue";
import axios from "axios";

export default defineComponent({
  name: "SignIn",
  components: {
    CustomInput,
    CustomButton,
  },
  data() {
    return {
      email: "",
      password: "",
    };
  },
  computed: {
    isEmailValid(): boolean {
      const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
      return emailRegex.test(this.email);
    },

    isPasswordValid(): boolean {
      if (this.password == "" || this.password == null) return false;
      else return true; //TODO: перерробити додати умови , поки буде так, щоб було простіше розробляти
    },

    isButtonDisabled(): boolean {
      return !this.isEmailValid || !this.isPasswordValid;
    },
  },
  methods: {
    saveUserDataToLocalStorage(userDataFromResponse: object): void {
      const map = new Map(Object.entries(userDataFromResponse));
      map.forEach((value, key) => localStorage.setItem(key, value));
    },
    async signIn() {
      const userData = {
        email: this.email,
        password: this.password,
      };
      await axios
        .post("/api/Auth/Login", JSON.stringify(userData), {
          headers: {
            "content-type": "application/json",
          },
        })
        .then((Response) => {
          if (Response.status === 200) {
            this.saveUserDataToLocalStorage(Response.data);
            this.$router.push("/");
          } else {
            alert("User was not found.");
          }
        });
    },
  },
});
</script>

<style scoped>
form {
  display: flex;
  flex-direction: column;
  max-width: 300px;
  margin: auto;
}

.btn {
  width: 100%;
}

label {
  margin-bottom: 8px;
}
</style>
