import React, { useState } from 'react';
import Chatbox from './Chatbox';

const App = () => {
  const [showChatbox, setShowChatbox] = useState(false);

  const handleOpenChatbox = () => {
    setShowChatbox(true);
  };

  const handleCloseChatbox = () => {
    setShowChatbox(false);
  };

  return (
    <div>
      {/* Your other content */}
      <button onClick={handleOpenChatbox}>Start Chat</button>
      {showChatbox && <Chatbox onClose={handleCloseChatbox} />}
    </div>
  );
};

export default App;
