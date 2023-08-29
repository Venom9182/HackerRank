import React from 'react';
import './ContactFormModal.css';

const ContactFormModal = () => {
  return (
    <div className="contact-us-page">
      <h1 className="contact-heading">Contact Us</h1>
      <div className="contact-logos">
        <img src="logo.png" alt="Logo" className="contact-logo" />
        <img src="email-logo.png" alt="Email Logo" className="contact-logo" />
        <img src="chat-logo.png" alt="Chat Logo" className="contact-logo" />
      </div>
      <div className="contact-options">
        <div className="contact-option">
          <h2>By Phone</h2>
          <p>Call the member of IT staff</p>
          <p>1234-567-789</p>
        </div>
        <div className="contact-option">
          <h2>By E-mail</h2>
          <p>E-mail us and get your problem solved</p>
          <p>HelpDesk@sc.com</p>
          <button className="start-chat-button">Start Chat</button>
        </div>
        <div className="contact-option">
          <h2>Live Chat</h2>
          <p>Chat with our in-house support</p>
          <button className="start-chat-button">Start Chat</button>
        </div>
      </div>
    </div>
  );
};

export default ContactFormModal;
