import React, { useState } from 'react';
import './Chatbox.css';

const Chatbox = ({ onClose }) => {
  const [message, setMessage] = useState('');
  const [chat, setChat] = useState([]);

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
