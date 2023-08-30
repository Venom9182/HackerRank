import React, { useState } from 'react';
import './ContactFormModal.css';
import Chatbox from './Chatbox'; // Import the Chatbox component

const ContactFormModal = () => {
  const [showChatbox, setShowChatbox] = useState(false);

  const handleOpenChatbox = () => {
    setShowChatbox(true);
  };

  const handleCloseChatbox = () => {
    setShowChatbox(false);
  };

  return (
    <div className="contact-us-page">
      {/* ... your existing Contact Us content ... */}
      <button className="start-chat-button" onClick={handleOpenChatbox}>
        Start Chat
      </button>
      {showChatbox && <Chatbox onClose={handleCloseChatbox} />}
    </div>
  );
};

export default ContactFormModal;
