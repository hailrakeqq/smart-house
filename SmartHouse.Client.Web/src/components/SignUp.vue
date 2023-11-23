<template>
  <div>
    <h2>Sign Up</h2>
    <form @submit.prevent="signUp">
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
        placeholder="Enter password"
      />
      <span v-if="!isPasswordValid">Please enter valid password.</span>

      <CustomInput
        id="confirmPassword"
        label="Confirm Password:"
        type="password"
        v-model="confirmPassword"
        placeholder="Enter confirm password"
      />
      <span v-if="!isConfirmPasswordValid">Please retype password.</span>

      <CustomButton
        :is-button-disabled="isButtonDisabled"
        class="btn"
        @click="signUp"
        >Sign Up</CustomButton
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
  name: "SignUp",
  components: {
    CustomInput,
    CustomButton,
  },
  data() {
    return {
      email: "",
      password: "",
      confirmPassword: "",
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

    isConfirmPasswordValid(): boolean {
      return this.password == this.confirmPassword;
    },

    isButtonDisabled(): boolean {
      return (
        !this.isConfirmPasswordValid ||
        !this.isEmailValid ||
        !this.isPasswordValid
      );
    },
  },
  methods: {
    signUp() {
      const user = {
        id: "",
        email: this.email,
        password: this.password,
      };
      axios
        .post("/api/Auth/Registration", JSON.stringify(user), {
          headers: {
            "Content-Type": "application/json",
          },
        })
        .then((response) => {
          if (response.status === 200) {
            alert("You successfully create account. Redirect to login.");
            this.$router.push({ path: "/sign-in" });
          } else {
            alert("Error. Account with these name or email already exist");
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

label {
  margin-bottom: 8px;
}
</style>
