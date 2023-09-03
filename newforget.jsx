import React, { useState } from 'react';
import './ForgotPassword.css';

const ForgotPassword = () => {
  const [email, setEmail] = useState('');
  const [otp, setOtp] = useState('');
  const [isEmailSent, setIsEmailSent] = useState(false);
  const [isOtpVerified, setIsOtpVerified] = useState(false);
  const [newPassword, setNewPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');

  const handleEmailSubmit = (e) => {
    e.preventDefault();

    // TODO: Implement email sending logic here
    // Simulate email sending by setting isEmailSent to true
    setIsEmailSent(true);
  };

  const handleOtpSubmit = (e) => {
    e.preventDefault();

    // TODO: Implement OTP verification logic here
    // For demonstration purposes, we'll just check if the OTP is '123456'
    if (otp === '123456') {
      setIsOtpVerified(true);
    } else {
      alert('Incorrect OTP. Please try again.');
    }
  };

  const handleChangePassword = (e) => {
    e.preventDefault();

    // TODO: Implement password change logic here
    // Check if newPassword and confirmPassword match, then proceed to change the password
    if (newPassword === confirmPassword) {
      alert('Password changed successfully.');
    } else {
      alert('Passwords do not match. Please try again.');
    }
  };

  return (
    <div className="forgot-password">
      <h2>Forgot Password</h2>
      {isEmailSent ? (
        isOtpVerified ? (
          <form onSubmit={handleChangePassword}>
            <p>Enter a new password:</p>
            <input
              type="password"
              placeholder="New Password"
              value={newPassword}
              onChange={(e) => setNewPassword(e.target.value)}
              required
            />
            <p>Confirm the new password:</p>
            <input
              type="password"
              placeholder="Confirm Password"
              value={confirmPassword}
              onChange={(e) => setConfirmPassword(e.target.value)}
              required
            />
            <button type="submit">Change Password</button>
          </form>
        ) : (
          <form onSubmit={handleOtpSubmit}>
            <p>An OTP has been sent to your email. Please enter it below:</p>
            <input
              type="text"
              placeholder="Enter OTP"
              value={otp}
              onChange={(e) => setOtp(e.target.value)}
              required
            />
            <button type="submit">Submit OTP</button>
          </form>
        )
      ) : (
        <form onSubmit={handleEmailSubmit}>
          <p>Enter your email address to reset your password:</p>
          <input
            type="email"
            placeholder="Email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            required
          />
          <button type="submit">Send OTP</button>
        </form>
      )}
    </div>
  );
};

export default ForgotPassword;
