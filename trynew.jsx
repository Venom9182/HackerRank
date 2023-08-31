import React, { useState, useEffect } from 'react';
import './Chatbox.css';

const Chatbox = ({ onClose }) => {
  const [message, setMessage] = useState('');
  const [chat, setChat] = useState([]);

  useEffect(() => {
    // Simulate AI responses after a short delay
    if (chat.length === 1 && chat[0].user === 'user') {
      setTimeout(() => {
        setChat([...chat, { text: 'How can I help you?', user: 'ai' }]);
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
      if (message.toLowerCase() === '1') {
        setTimeout(() => {
          setChat([...chat, { text: 'FAQs', user: 'ai' }]);
        }, 1000);
      } else if (message.toLowerCase() === '2') {
        setTimeout(() => {
          setChat([...chat, { text: 'Recent Articles', user: 'ai' }]);
        }, 1000);
      } else if (message.toLowerCase() === '3') {
        setTimeout(() => {
          setChat([...chat, { text: 'Connecting to an Agent...', user: 'ai' }]);
        }, 1000);
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
