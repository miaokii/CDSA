
//
//  Ex.swift
//  Home
//
//  Created by miaokii on 2020/5/7.
//  Copyright © 2020 ly. All rights reserved.
//

import Foundation
import UIKit
import MJRefresh

extension UIColor {
    static let theme = #colorLiteral(red: 0.07667491585, green: 0.8229058385, blue: 0.9066591263, alpha: 1)
    static let background = UIColor.tableGroupedBackgroundColor
    
    static let viewBackgroundColorLevel1 = UIColor.tableCellGroupedBackgroundColor

    static let textColorLevel1 = UIColor.for(light: .init(hex: 0x333333), dark: .init(hex: 0x999898))
    static let textColorLevel2 = UIColor.init(hex: 0x666666)
    
    static let niceBlack = UIColor.init(hex: 0x1E2028)
    static let niceRed = UIColor.init(hex: 0xED4252)
    
    static let tableViewBackground = UIColor.for(light: UIColor.init(hex: 0xf7f7f7))
    static let corange = UIColor.init(hex: 0xFF5F2C)
}

public extension UIColor {
    convenience init(hex: UInt32) {
        var red, green, blue, alpha: UInt32
        if hex > 0xffffff {
            blue = hex & 0x000000ff
            green = (hex & 0x0000ff00) >> 8
            red = (hex & 0x00ff0000) >> 16
            alpha = (hex & 0xff000000) >> 24
        } else {
            blue = hex & 0x0000ff
            green = (hex & 0x00ff00) >> 8
            red = (hex & 0xff0000) >> 16
            alpha = 255
        }
        self.init(red: CGFloat(red) / (255.0), green: CGFloat(green) / 255.0, blue: CGFloat(blue) / 255.0, alpha: CGFloat(alpha) / 255.0)
    }
    
    class func `for`(light: UIColor, dark: UIColor? = nil) -> UIColor {
        if #available(iOS 13.0, *) {
            if dark == nil {
                var red: CGFloat = 0, green: CGFloat = 0, blue: CGFloat = 0, alpha: CGFloat = 0
                light.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
                return UIColor(dynamicProvider: { $0.userInterfaceStyle == .light ? light : UIColor(red: 1 - red, green: 1 - green, blue: 1 - blue, alpha: alpha) })
            } else {
                return UIColor(dynamicProvider: { $0.userInterfaceStyle == .light ? light : dark! })
            }
        } else {
            return light
        }
    }
    
    class var random: UIColor {
        get {
            return UIColor(hex: arc4random() % 0xffffff)
        }
    }
    
    class var separatorColor: UIColor {
        return UIColor(white: 0, alpha: 0.2)
    }
    
    class var systemBackgroundColor: UIColor {
        if #available(iOS 13.0, *) {
            return UIColor.systemBackground
        } else {
            return #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        }
    }
    
    static var tableGroupedBackgroundColor: UIColor {
        if #available(iOS 13.0, *) {
            return UIColor.systemGroupedBackground
        } else {
            return #colorLiteral(red: 0.9490196078, green: 0.9490196078, blue: 0.968627451, alpha: 1)
        }
    }
    
    class var tableCellGroupedBackgroundColor: UIColor {
        if #available(iOS 13.0, *) {
            return UIColor.value(forKey: "tableCellGroupedBackgroundColor") as! UIColor
        }
        return #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
    }
}

extension UIView {
    var centerX: CGFloat {
        set {
            center.x = newValue
        }
        
        get{
            return center.x
        }
    }
}



class DYLoadingView: UIView {
    
    /// 球的宽度
    var indicatorWidth: CGFloat = 12
    /// 动画速度，每1/60秒移动的距离
    var indicatorSpeed: CGFloat = 0.7
    /// 球的缩放尺寸
    var indicatorScale: CGFloat = 0.25
    /// 动画暂停时间，一次交换完成后暂停的时间
    var indicatorPauseSecond: CGFloat = 0.15
    /// 绿球颜色
    var indication1Color = UIColor.init(hex: 0x0AC8E0)
    /// 红球颜色
    var indication2Color = UIColor.init(hex: 0xFF5F2C)
    /// 交集颜色
    var overlapColor = UIColor.background
    
    /// 红球
    private var redView = UIView()
    /// 绿球
    private var greenView = UIView()
    /// 重叠的球
    private var overView = UIView()
    /// timer
    private var displayLink: CADisplayLink!
    ///
    private var containerView = UIView()
    /// 动画方向，正表示正向，负表示反向
    private var directionStep: CGFloat!
    /// 正在动画
    var isLoading = false
    
    @discardableResult
    class func showIn(view: UIView) -> DYLoadingView {
        let loadingView = DYLoadingView.init(frame: view.bounds)
        view.addSubview(loadingView)
        loadingView.startAnimation()
        return loadingView
    }
    
    @discardableResult
    class func hideIn(view: UIView) -> Bool {
        for view in view.subviews where view is DYLoadingView {
            let loadingView = view as! DYLoadingView
            loadingView.stopAnimation()
            loadingView.removeFromSuperview()
            return true
        }
        return false
    }
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setup()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        setup()
    }
    
    private func setup() {
    
        containerView.frame = CGRect.init(x: 0, y: 0, width: 2 * indicatorWidth, height: indicatorWidth)
        containerView.center = self.center
        addSubview(containerView)
        
        greenView = UIView.init()
        greenView.backgroundColor = indication1Color
        greenView.frame = CGRect.init(x: 0, y: 0, width: indicatorWidth, height: indicatorWidth)
        greenView.layer.cornerRadius = indicatorWidth / 2
        greenView.layer.masksToBounds = true
        containerView.addSubview(greenView)
        
        redView = UIView.init()
        redView.backgroundColor = indication2Color
        redView.frame = CGRect.init(x: indicatorWidth, y: 0, width: indicatorWidth, height: indicatorWidth)
        redView.layer.cornerRadius = indicatorWidth / 2
        redView.layer.masksToBounds = true
        containerView.addSubview(redView)
        containerView.bringSubviewToFront(greenView)
        
        overView = UIView.init()
        overView.backgroundColor = overlapColor
        overView.frame = .init(x: 0, y: 0, width: indicatorWidth, height: indicatorWidth)
        overView.layer.cornerRadius = indicatorWidth / 2
        overView.layer.masksToBounds = true
        greenView.addSubview(overView)
        
        directionStep = indicatorSpeed
        /// 动画
        displayLink = CADisplayLink.init(target: self, selector: #selector(updateIndicator))
    }
}

extension DYLoadingView {
    
    @objc private func updateIndicator() {
        
        var greenCenter = greenView.center
        greenCenter.x += directionStep
        greenView.center = greenCenter
        
        var redCenter = redView.center
        redCenter.x -= directionStep
        redView.center = redCenter
        
        // 正向时，绿球变大，红球变小
        // 反向时，红球变大，绿球变小
        let largerView = directionStep > 0 ? greenView : redView
        let smallView = directionStep > 0 ? redView : greenView
        largerTransformOf(view: largerView)
        smallerTransformOf(view: smallView)
        
        // 重叠的位置
        overView.frame = smallView.convert(smallView.bounds, to: largerView)
        overView.layer.cornerRadius = overView.bounds.size.width / 2
        
        // 当绿球左边 >= 红球右边，且方向为正向时，应该切换方向了
        // 红球切换到绿球上面
        if greenView.frame.minX >= redView.frame.maxX, directionStep > 0 {
            directionStep = -indicatorSpeed
            containerView.bringSubviewToFront(redView)
            redView.addSubview(overView)
            pauseAnimation()
        }
        // 当红球左边 >= 绿球左边，且方向为负向时，应该切换方向了
        // 绿球切换到红球上面
        else if redView.frame.minX > greenView.frame.maxX, directionStep < 0 {
            directionStep = indicatorSpeed
            containerView.bringSubviewToFront(greenView)
            greenView.addSubview(overView)
            pauseAnimation()
        }
    }
    
    /// 放大变换
    private func largerTransformOf(view: UIView) {
        let cosy = valueOf(centerX: view.centerX) * indicatorScale
        view.transform = CGAffineTransform.init(scaleX: 1 + cosy, y: 1 + cosy)
    }
    
    /// 缩小变换
    private func smallerTransformOf(view: UIView) {
        let cosy = valueOf(centerX: view.centerX) * indicatorScale
        view.transform = CGAffineTransform.init(scaleX: 1 - cosy, y: 1 - cosy)
    }
    
    /// 根据cos来变换
    private func valueOf(centerX: CGFloat) -> CGFloat {
        /// 球心到container中心的距离
        let apart = centerX - containerView.bounds.size.width / 2
        /// 球心到container中心的最大距离
        let maxApart = (containerView.bounds.size.width - indicatorWidth) / 2
        /// 换算角度
        let angle = apart * (.pi / 2) / maxApart
        /// 余玄值
        return cos(angle)
    }
    
    func startAnimation() {
        guard !isLoading else {
            return
        }
        isLoading = true
        displayLink.add(to: .main, forMode: .common)
    }
    
    func stopAnimation() {
        guard isLoading else {
            return
        }
        isLoading = false
        displayLink.remove(from: .main, forMode: .common)
    }
    
    private func pauseAnimation() {
        let temDirectionStep = directionStep
        directionStep = 0
        DispatchQueue.main.asyncAfter(deadline: .now() + .init(indicatorPauseSecond)) {
            self.directionStep = temDirectionStep
        }
    }
}

/// 抖音Loading
class LoadingView: UIView {
    
    private var hud: DYLoadingView!
    
    override init(frame: CGRect) {
        super.init(frame: UIScreen.main.bounds)
        
        self.backgroundColor = .init(white: 0.3, alpha: 0.3)
        
        let tapGesture = UITapGestureRecognizer.init(target: self, action: #selector(handleGuesture(_:)))
        self.addGestureRecognizer(tapGesture)
        
        hud = DYLoadingView.showIn(view: self)
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }

    deinit {
        print("deinit -----> \(NSStringFromClass(self.classForCoder))")
    }
}

extension LoadingView {
    
    @objc private func handleGuesture(_ gesture: UIGestureRecognizer) {
        hide()
    }
    
    func show() {
        // 如果添加到cell上会跟随tableView滑动
        let window = UIApplication.shared.keyWindow
        window?.addSubview(self)
        self.alpha = 0
        UIView.animate(withDuration: 0.25) {
            self.alpha = 1
        }
    }
    
    func hide(complete:(()->())? = nil) {
        UIView.animate(withDuration: 0.25,
                       animations: {
                           self.alpha = 0
        }) { (_) in
            complete?()
            self.removeFromSuperview()
        }
    }
}

class MJDyRefresh: MJRefreshHeader {
    
    private var hud: DYLoadingView!
    
    override func prepare() {
        super.prepare()
        mj_h = 50
        isAutomaticallyChangeAlpha = true
    }
    
    override func placeSubviews() {
        super.placeSubviews()
        if hud == nil {
            hud = DYLoadingView.showIn(view: self)
            hud.stopAnimation()
        }
    }
    
    override func scrollViewContentOffsetDidChange(_ change: [AnyHashable : Any]!) {
        super.scrollViewContentOffsetDidChange(change)
    }
    
    override func scrollViewContentSizeDidChange(_ change: [AnyHashable : Any]!) {
        super.scrollViewContentSizeDidChange(change)
    }
    
    override func scrollViewPanStateDidChange(_ change: [AnyHashable : Any]!) {
        super.scrollViewPanStateDidChange(change)
    }
    
    override var state: MJRefreshState {
        didSet {
            guard hud != nil else {
                return
            }
            switch state {
                // 闲置状态
            case .idle:
                hud.stopAnimation()
                // 松开就刷新
            case .pulling:
                hud.stopAnimation()
                // 正在刷新
            case .refreshing:
                hud.startAnimation()
            default:
                break
            }
        }
    }
}

class MJDyFooter: MJRefreshBackFooter {
    private var hudView: UIImageView!
    private var hintLabel: UILabel!
    
    override func prepare() {
        super.prepare()
        mj_h = 50
        isAutomaticallyChangeAlpha = true
        
        hudView = UIImageView.init(image: UIImage.init(named: "footer_lood"))
        self.addSubview(hudView)
        
        hintLabel = UILabel.init()
        hintLabel.font = UIFont.systemFont(ofSize: 14)
        hintLabel.textColor = .textColorLevel2
        hintLabel.textAlignment = .center
        self.addSubview(hintLabel)
        
    }
    
    override func placeSubviews() {
        super.placeSubviews()

        hintLabel.snp.makeConstraints { (snp) in
            snp.centerY.equalToSuperview()
            snp.centerX.equalToSuperview().offset(10)
        }
        
        hudView.snp.makeConstraints { (snp) in
            snp.centerY.equalToSuperview()
            snp.right.equalTo(hintLabel.snp.left).offset(-10)
        }
    }
    
    override func scrollViewContentOffsetDidChange(_ change: [AnyHashable : Any]!) {
        super.scrollViewContentOffsetDidChange(change)
    }
    
    override func scrollViewContentSizeDidChange(_ change: [AnyHashable : Any]!) {
        super.scrollViewContentSizeDidChange(change)
    }
    
    override func scrollViewPanStateDidChange(_ change: [AnyHashable : Any]!) {
        super.scrollViewPanStateDidChange(change)
    }
    
    override var state: MJRefreshState {
        didSet {
            hudView.isHidden = state == .noMoreData
            switch state {
                // 闲置状态
            case .idle:
                hintLabel.text = "上拉刷新"
                cancelAnimation()
                // 松开就刷新
            case .pulling:
                hintLabel.text = "松开刷新"
                cancelAnimation()
                // 正在刷新
            case .refreshing:
                startAnimation()
                hintLabel.text = "正在刷新..."
            case .noMoreData:
                hintLabel.text = "没有更多数据了！"
                cancelAnimation()
            default:
                break
            }
        }
    }
    
    private func startAnimation() {
        hudView.layer.add(annotation, forKey: "centerLayer")
    }
    
    private func cancelAnimation() {
        hudView.layer.removeAllAnimations()
    }
    
    private var annotation: CAAnimation {
        let caAnimation = CABasicAnimation.init(keyPath: "transform.rotation.z")
        caAnimation.fromValue = 0
        caAnimation.toValue = Double.pi * 2
        caAnimation.duration = 1
        caAnimation.repeatCount = HUGE
        return caAnimation
    }
}
