import React, { useState } from 'react';
import { Link } from 'react-router-dom';

const ForgotPassword = () => {
  const [email, setEmail] = useState('');
  const [otpRequested, setOtpRequested] = useState(false);

  const handleEmailChange = (e) => {
    setEmail(e.target.value);
  };

  const handleRequestOTP = () => {
    // Logic to send OTP to the provided email goes here
    // You can implement this part as needed

    // For this example, we'll just set otpRequested to true
    setOtpRequested(true);
  };

  return (
    <div className="forgot-password-page">
      <h2>Forgot Password</h2>
      {!otpRequested ? (
        <>
          <p>Please enter your email address to request an OTP:</p>
          <input
            type="email"
            placeholder="Enter your email"
            value={email}
            onChange={handleEmailChange}
          />
          <button onClick={handleRequestOTP}>Request OTP</button>
        </>
      ) : (
        <>
          <p>An OTP has been sent to your email address.</p>
          <p>Please check your email and enter the OTP below:</p>
          {/* Add OTP input field and validation here */}
          <input type="text" placeholder="Enter OTP" />
          <button>Submit OTP</button>
        </>
      )}
      <p>
        Remember your password? <Link to="/login">Back to Login</Link>
      </p>
    </div>
  );
};

export default ForgotPassword;
