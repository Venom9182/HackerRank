import React from 'react';

const ContactUs = () => {
  return (
    <div className="contact-us-container">
      <div className="contact-header">
        <img src="/path/to/your/logo.png" alt="Logo" className="logo" />
        <h1>Contact Us</h1>
      </div>
      <div className="contact-options">
        <div className="contact-option">
          <img src="/path/to/phone-icon.png" alt="Phone" className="contact-icon" />
          <p>By Phone</p>
          <p>1234-567-789</p>
        </div>
        <div className="contact-option">
          <img src="/path/to/email-icon.png" alt="Email" className="contact-icon" />
          <p>By E-mail</p>
          <p>HelpDesk@sc.com</p>
        </div>
        <div className="contact-option">
          <img src="/path/to/chat-icon.png" alt="Chat" className="contact-icon" />
          <p>Live Chat</p>
          <button>Start Chat</button>
        </div>
      </div>
    </div>
  );
}

export default ContactUs;
