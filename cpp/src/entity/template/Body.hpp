virtual bool isCollidingPoint(const GameVector&) const override;
virtual void reactToCollision(const float, const GameVector&, const GameVector&, float);
virtual GameRect getWrapper(float) const override;
virtual float getLeftest() const override;
virtual float getRightest() const override;
virtual float getToppest() const override;
virtual float getBottest() const override;
virtual GameVector getSpeedAt(const GameVector&) const override;
virtual GameRect getRenderGameRect() const override;
