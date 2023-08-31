import React, { useState, useEffect } from 'react';
import './Chatbox.css';

const Chatbox = ({ onClose }) => {
  const [message, setMessage] = useState('');
  const [chat, setChat] = useState([]);
  const [showOptions, setShowOptions] = useState(false);

  useEffect(() => {
    if (chat.length === 1 && chat[0].user === 'user') {
      setTimeout(() => {
        setChat([...chat, { text: 'Hi', user: 'ai' }]);
        setTimeout(() => {
          setChat([
            ...chat,
            { text: 'How can I help you?', user: 'ai' },
            { text: '1. FAQs', user: 'ai' },
            { text: '2. Recent Articles', user: 'ai' },
            { text: '3. Chat with an Agent', user: 'ai' },
          ]);
          setShowOptions(true);
        }, 1000);
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

      if (showOptions) {
        switch (message.toLowerCase()) {
          case '1':
            setChat([...chat, { text: 'FAQs', user: 'ai' }]);
            break;
          case '2':
            setChat([...chat, { text: 'Recent Articles', user: 'ai' }]);
            break;
          case '3':
            setChat([...chat, { text: 'Connecting to an Agent...', user: 'ai' }]);
            break;
          default:
            setChat([...chat, { text: 'I am not sure what you mean.', user: 'ai' }]);
        }
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
