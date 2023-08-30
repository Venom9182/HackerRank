import React, { useState, useEffect } from 'react';
import './Chatbox.css';

const Chatbox = ({ onClose }) => {
  const [message, setMessage] = useState('Hi');
  const [chat, setChat] = useState([]);

  useEffect(() => {
    // Simulate AI responses after a short delay
    if (chat.length === 1 && chat[0].user === 'user') {
      const aiResponse = "How can I help you?\n1. FAQs\n2. Recent Articles\n3. Chat with an Agent";
      setTimeout(() => {
        setChat([...chat, { text: aiResponse, user: 'ai' }]);
      }, 1000);
    }
  }, [chat]);

  const handleInputChange = (e) => {
    setMessage(e.target.value);
  };

  const handleSend = () => {
    if (message.trim() !== '') {
      setChat([...chat, { text: message, user: 'user' }]);
      setMessage('');

      // Simulate AI response for user options
      if (message.toLowerCase() === '1' || message.toLowerCase() === '2' || message.toLowerCase() === '3') {
        const aiResponse = "Connecting you to an Agent...";
        setChat([...chat, { text: aiResponse, user: 'ai' }]);
      }
    }
  };

  const handleKeyPress = (e) => {
    if (e.key === 'Enter') {
      handleSend();
    }
  };

  return (
    <div className="chatbox">
      <div className="chatbox-header">
        <span className="chatbox-title">Alex</span>
        <button className="chatbox-close" onClick={onClose}>
          &#10006;
        </button>
      </div>
      <div className="chatbox-content">
        {chat.map((message, index) => (
          <div key={index} className={`message ${message.user}`}>
            {message.text}
          </div>
        ))}
      </div>
      <div className="chatbox-input">
        <input
          type="text"
          placeholder="Type your message..."
          value={message}
          onChange={handleInputChange}
          onKeyPress={handleKeyPress}
        />
        <button className="send-button" onClick={handleSend}>
          Send
        </button>
      </div>
    </div>
  );
};

export default Chatbox;
