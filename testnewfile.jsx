import React, { useState, useEffect } from 'react';
import './Chatbox.css';

const Chatbox = ({ onClose }) => {
  const [message, setMessage] = useState('');
  const [chat, setChat] = useState([]);
  const [aiResponses, setAiResponses] = useState([]);

  useEffect(() => {
    if (message === '1' || message === '2' || message === '3') {
      setChat([...chat, { text: `You chose option ${message}`, user: 'user' }]);

      // Simulate AI response for user options
      setTimeout(() => {
        setChat([...chat, { text: aiResponses[parseInt(message) - 1], user: 'ai' }]);
      }, 1000);
    } else if (message.trim() !== '') {
      setChat([...chat, { text: message, user: 'user' }]);
    }
  }, [message]);

  useEffect(() => {
    // Simulate AI responses after a short delay
    setTimeout(() => {
      setAiResponses([
        'How can I help you?\n1. FAQs\n2. Recent Articles\n3. Chat with an Agent',
        'You are now viewing FAQs.\n1. How do I reset my password?\n2. How to contact support?',
        'You are now viewing Recent Articles.\n1. New features in our app.\n2. Tips for better productivity.',
        'Connecting to an Agent...',
      ]);
    }, 1000);
  }, []);

  const handleInputChange = (e) => {
    setMessage(e.target.value);
  };

  const handleSend = () => {
    if (message.trim() !== '') {
      setChat([...chat, { text: message, user: 'user' }]);
      setMessage('');
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
