import React, { useState } from 'react';
import './Chatbox.css';

const Chatbox = ({ onClose }) => {
  const [messages, setMessages] = useState([]);
  const [newMessage, setNewMessage] = useState('');

  const handleSendMessage = () => {
    if (newMessage.trim() !== '') {
      setMessages([...messages, { text: newMessage, sender: 'user' }]);
      setNewMessage('');
    }
  };

  return (
    <div className="chatbox">
      <div className="chatbox-header">
        <span className="chatbox-title">Alex</span>
        <button className="chatbox-close-button" onClick={onClose}>
          &#10006;
        </button>
      </div>
      <div className="chatbox-messages">
        {messages.map((message, index) => (
          <div
            key={index}
            className={`chatbox-message ${message.sender === 'user' ? 'user' : 'agent'}`}
          >
            {message.text}
          </div>
        ))}
      </div>
      <div className="chatbox-input">
        <input
          type="text"
          placeholder="Type your message..."
          value={newMessage}
          onChange={(e) => setNewMessage(e.target.value)}
        />
        <button className="chatbox-send-button" onClick={handleSendMessage}>
          Send
        </button>
      </div>
    </div>
  );
};

export default Chatbox;
