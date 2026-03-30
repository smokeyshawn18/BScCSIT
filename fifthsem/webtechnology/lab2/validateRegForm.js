function validateForm(event) {
  event.preventDefault();
  clearErrors();

  let isValid = true;

  // 1. First Name: Alphabets only, min 6 characters
  const firstName = document.getElementById("firstName").value.trim();
  if (!firstName) {
    showError("firstNameError", "First Name is required");
    isValid = false;
  } else if (!/^[A-Za-z]{6,}$/.test(firstName)) {
    showError("firstNameError", "Alphabets only, min 6 chars");
    isValid = false;
  }

  // 2. Last Name: Not empty
  const lastName = document.getElementById("lastName").value.trim();
  if (!lastName) {
    showError("lastNameError", "Last Name required");
    isValid = false;
  }

  // 3. Email: Standard pattern
  const email = document.getElementById("email").value.trim();
  if (!email) {
    showError("emailError", "Email required");
    isValid = false;
  } else if (!/^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$/.test(email)) {
    showError("emailError", "Valid email required");
    isValid = false;
  }

  // 4. Mobile: Exactly 10 digits
  const mobile = document.getElementById("mobile").value.replace(/\D/g, "");
  if (!mobile) {
    showError("mobileError", "Mobile required");
    isValid = false;
  } else if (mobile.length !== 10) {
    showError("mobileError", "Exactly 10 digits");
    isValid = false;
  }

  // 5. Password: Min 6 characters
  const password = document.getElementById("password").value;
  if (!password) {
    showError("passwordError", "Password required");
    isValid = false;
  } else if (password.length < 6) {
    showError("passwordError", "Min 6 characters");
    isValid = false;
  }

  // 6. Address: Not empty
  const address = document.getElementById("address").value.trim();
  if (!address) {
    showError("addressError", "Address required");
    isValid = false;
  }

  if (isValid) {
    alert("Registration Successful!");
  }
  return false;
}

function showError(id, message) {
  document.getElementById(id).innerHTML = message;
  document.getElementById(id).style.display = "block";
}

function clearErrors() {
  const errors = [
    "firstNameError",
    "lastNameError",
    "emailError",
    "mobileError",
    "passwordError",
    "addressError",
  ];
  errors.forEach((id) => {
    document.getElementById(id).style.display = "none";
    document.getElementById(id).innerHTML = "";
  });
}

// to use this in a html
// <form id="registerForm" onsubmit="return validateForm(event)">
//   form fields here
//     <input type="submit" value="Register">
// </form>
