import React, { useState } from 'react';
import './Chatbox.css';
import AIChatbot from './AIChatbot'; // Import the AIChatbot component

const Chatbox = ({ onClose }) => {
  const [message, setMessage] = useState('');
  const [chat, setChat] = useState([]);
  const [showAIChatbot, setShowAIChatbot] = useState(false);

  const handleInputChange = (e) => {
    setMessage(e.target.value);
  };

  const handleSend = () => {
    if (message.trim() !== '') {
      setChat([...chat, { text: message, user: 'user' }]);
      setMessage('');

      // Handle user's message
      handleUserMessage(message);
    }
  };

  const handleKeyPress = (e) => {
    if (e.key === 'Enter') {
      handleSend();
    }
  };

  const handleOpenAIChatbot = () => {
    setShowAIChatbot(true);
  };

  const handleCloseAIChatbot = () => {
    setShowAIChatbot(false);
  };

  const handleUserMessage = (message) => {
    // Handle user's message here

    // For example, open AI Chatbot if the user sends "chat"
    if (message.toLowerCase() === 'chat') {
      setShowAIChatbot(true);
      setChat([...chat, { text: 'Connecting you to an agent...', user: 'ai' }]);
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
        <button className="ai-button" onClick={handleOpenAIChatbot}>
          Open AI Chatbot
        </button>
        {showAIChatbot && <AIChatbot onClose={handleCloseAIChatbot} />}
      </div>
    </div>
  );
};

export default Chatbox;
