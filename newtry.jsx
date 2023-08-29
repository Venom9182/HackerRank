import React from 'react';
import './ContactUs.css'; // Import your CSS file for ContactUs
import phoneIcon from './phone-icon.png'; // Import your phone icon image
import emailIcon from './email-icon.png'; // Import your email icon image
import chatIcon from './chat-icon.png'; // Import your chat icon image

const ContactUs = () => {
  return (
    <div className="contact-us-page">
      <h1 className="contact-heading">Contact Us</h1>
      <div className="contact-options">
        <div className="contact-option">
          <img src={phoneIcon} alt="Phone Icon" className="contact-icon" />
          <p>By Phone</p>
        </div>
        <div className="contact-option">
          <img src={emailIcon} alt="Email Icon" className="contact-icon" />
          <p>By E-mail</p>
        </div>
        <div className="contact-option">
          <img src={chatIcon} alt="Chat Icon" className="contact-icon" />
          <p>Live Chat</p>
        </div>
      </div>
      <button className="start-chat-button">Start Chat</button>
    </div>
  );
}

export default ContactUs;
