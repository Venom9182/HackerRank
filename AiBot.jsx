import React, { useState, useEffect } from 'react';

const AIChatbot = ({ onClose }) => {
  const [message, setMessage] = useState('');
  const [chat, setChat] = useState([]);

  useEffect(() => {
    // Simulate AI responses after a short delay
    if (chat.length % 2 === 1) {
      const aiResponse = 'AI Response Placeholder';
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

      // Simulate AI response
      const aiResponse = 'AI Response Placeholder';
      setChat([...chat, { text: aiResponse, user: 'ai' }]);
    }
  };

  const handleKeyPress = (e) => {
    if (e.key === 'Enter') {
      handleSend();
    }
  };

  return (
    <div className="ai-chatbot">
      <div className="ai-chatbot-header">
        <span className="ai-chatbot-title">AI Chatbot</span>
        <button className="ai-chatbot-close" onClick={onClose}>
          &#10006;
        </button>
      </div>
      <div className="ai-chatbot-content">
        {chat.map((message, index) => (
          <div key={index} className={`message ${message.user}`}>
            {message.text}
          </div>
        ))}
      </div>
      <div className="ai-chatbot-input">
        <input
          type="text"
          placeholder="Type your message..."
          value={message}
          onChange={handleInputChange}
          onKeyPress={handleKeyPress}
        />
        <button className="ai-send-button" onClick={handleSend}>
          Send
        </button>
      </div>
    </div>
  );
};

export default AIChatbot;
