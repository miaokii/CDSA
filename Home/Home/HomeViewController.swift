
//
//  HomeViewController.swift
//  Home
//
//  Created by miaokii on 2020/5/8.
//  Copyright © 2020 ly. All rights reserved.
//

import UIKit
import Parchment


class CustomPagingView: PagingView {
  
    static let HeaderHeight: CGFloat = 816
  
    var headerHeightConstraint: NSLayoutConstraint?
  
    private lazy var headerView: UIImageView = {
        let view = UIImageView(image: UIImage(named: "headImage"))
        view.contentMode = .scaleAspectFit
        view.clipsToBounds = true
        return view
    }()
  
    
  override func setupConstraints() {
    addSubview(headerView)

    headerView.snp.makeConstraints { (make) in
        make.top.left.right.equalToSuperview()
        make.height.equalTo(CustomPagingView.HeaderHeight)
    }
    
    collectionView.snp.makeConstraints { (make) in
        make.top.equalTo(headerView.snp.bottom)
        make.left.right.equalToSuperview()
        make.height.equalTo(options.menuHeight)
    }
    
    pageView.snp.makeConstraints { (make) in
        make.top.left.right.bottom.equalToSuperview()
    }
    
//    pageView.translatesAutoresizingMaskIntoConstraints = false
//    collectionView.translatesAutoresizingMaskIntoConstraints = false
//    headerView.translatesAutoresizingMaskIntoConstraints = false
//
//    headerHeightConstraint = headerView.heightAnchor.constraint(
//      equalToConstant: CustomPagingView.HeaderHeight
//    )
//    headerHeightConstraint?.isActive = true
//
//    NSLayoutConstraint.activate([
//      collectionView.leadingAnchor.constraint(equalTo: leadingAnchor),
//      collectionView.trailingAnchor.constraint(equalTo: trailingAnchor),
//      collectionView.heightAnchor.constraint(equalToConstant: options.menuHeight),
//      collectionView.topAnchor.constraint(equalTo: headerView.bottomAnchor),
//
//      headerView.topAnchor.constraint(equalTo: topAnchor),
//      headerView.leadingAnchor.constraint(equalTo: leadingAnchor),
//      headerView.trailingAnchor.constraint(equalTo: trailingAnchor),
//
//      pageView.leadingAnchor.constraint(equalTo: leadingAnchor),
//      pageView.trailingAnchor.constraint(equalTo: trailingAnchor),
//      pageView.bottomAnchor.constraint(equalTo: bottomAnchor),
//      pageView.topAnchor.constraint(equalTo: topAnchor)
//    ])
  }
}

// Create a custom paging view controller and override the view with
// our own custom subclass.
class CustomPagingViewController: PagingViewController<PagingIndexItem> {
  
  override func loadView() {
    view = CustomPagingView(
      options: options,
      collectionView: collectionView,
      pageView: pageViewController.view
    )
  }
}


class HomeViewController: UIViewController {
    private let pagingViewController = CustomPagingViewController()
    override func viewDidLoad() {
        super.viewDidLoad()
    
        // Add the paging view controller as a child view controller.
        addChild(pagingViewController)
        view.addSubview(pagingViewController.view)
        pagingViewController.didMove(toParent: self)
    
        // Customize the menu styling.
        pagingViewController.selectedTextColor = .black
        pagingViewController.indicatorColor = .corange
        pagingViewController.indicatorOptions = .visible(
            height: 8,
            zIndex: Int.max,
            spacing: .zero,
            insets: .zero
        )

        pagingViewController.view.snp.makeConstraints { (make) in
            make.edges.equalTo(0)
        }
    
        // Set our data source and delegate.
        pagingViewController.dataSource = self
        pagingViewController.delegate = self
    }
}

extension HomeViewController: PagingViewControllerDataSource {
  
  func pagingViewController<T>(_ pagingViewController: PagingViewController<T>, viewControllerForIndex index: Int) -> UIViewController {
    let viewController = VideoCollectionController()
    
    // Inset the table view with the height of the menu height.
    let height = pagingViewController.options.menuHeight + CustomPagingView.HeaderHeight
    let insets = UIEdgeInsets(top: height, left: 0, bottom: 0, right: 0)
    viewController.collectionView.contentInset = insets
    viewController.collectionView.scrollIndicatorInsets = insets
    viewController.collectionView.delegate = self
    
    return viewController
  }
  
  func pagingViewController<T>(_ pagingViewController: PagingViewController<T>, pagingItemForIndex index: Int) -> T {
    return PagingIndexItem(index: index, title: "View \(index)") as! T
  }
  
  func numberOfViewControllers<T>(in: PagingViewController<T>) -> Int{
    return 3
  }
  
}

extension HomeViewController: PagingViewControllerDelegate {
  
  func pagingViewController<T>(_ pagingViewController: PagingViewController<T>, didScrollToItem pagingItem: T, startingViewController: UIViewController?, destinationViewController: UIViewController, transitionSuccessful: Bool) {
    guard let startingViewController = startingViewController as? VideoCollectionController else { return }
    guard let destinationViewController = destinationViewController as? VideoCollectionController else { return }
    
    // Set the delegate on the currently selected view so that we can
    // listen to the scroll view delegate.
    if transitionSuccessful {
      startingViewController.collectionView.delegate = nil
      destinationViewController.collectionView.delegate = self
    }
  }
  
  func pagingViewController<T>(_ pagingViewController: PagingViewController<T>, willScrollToItem pagingItem: T, startingViewController: UIViewController, destinationViewController: UIViewController) {
    guard let destinationViewController = destinationViewController as? VideoCollectionController else { return }

    // Update the content offset based on the height of the header view.
    if let pagingView = pagingViewController.view as? CustomPagingView {
      if let headerHeight = pagingView.headerHeightConstraint?.constant {
        let offset = headerHeight + pagingViewController.options.menuHeight
        destinationViewController.collectionView.contentOffset = CGPoint(x: 0, y: -offset)
      }
    }
  }
  
}

extension HomeViewController: UICollectionViewDelegate {
  
  func scrollViewDidScroll(_ scrollView: UIScrollView) {
    print(scrollView.contentOffset.y)
    if let menuView = pagingViewController.view as? CustomPagingView {
//      let height = max(0, abs(scrollView.contentOffset.y) - pagingViewController.options.menuHeight)
//      menuView.headerHeightConstraint?.constant = height
        var menuViewFram = menuView.frame
        menuViewFram.origin.y = -(scrollView.contentOffset.y) - CustomPagingView.HeaderHeight - menuView.options.menuHeight
        menuView.frame = menuViewFram
    }
  }
  
}